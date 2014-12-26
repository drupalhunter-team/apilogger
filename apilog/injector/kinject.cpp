
#include "stdafx.h"
#define _WIN32_WINNT 0x0502
#include <windows.h>
#include "kinject.h"
#include "injector.h"


void KInject::InjectDll(HANDLE hProcess, HANDLE hThread, DWORD param){

	PFN_QueueUserAPC pQUAPC = (PFN_QueueUserAPC)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "QueueUserAPC" ) );
	pQUAPC(
		(PAPCFUNC)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"),
		hThread, 
		(DWORD)param
		);  
}

void KInject::Inject2(HANDLE hProcess, HANDLE hThread){
	DWORD ret;
	char szDLL[MAX_PATH];
	PFN_WriteProcessMemory pWriteProcessMemory = (PFN_WriteProcessMemory)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "WriteProcessMemory" ) );
	PFN_VirtualAllocEx pVirtualAllocEx = (PFN_VirtualAllocEx)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "VirtualAllocEx" ) );

	//Intruder.dll full path
	GetModuleFileNameA(0, szDLL, MAX_PATH);
	for(DWORD i=(DWORD)strlen(szDLL); i>0; i--){if(szDLL[i-1]=='\\'){szDLL[i]=0; break;}}
	strcat(szDLL, "intruder.dll");

	int len = strlen(szDLL) + 1;
	PVOID param = pVirtualAllocEx(hProcess, NULL, len, MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);  
	if (param != NULL)  
	{  
		if (pWriteProcessMemory(hProcess, param, (LPVOID)szDLL, len, &ret)) {  
			InjectDll(hProcess, hThread, (DWORD)param);   
		}  
	}
}

BOOL WINAPI KInject::InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile){
	BOOL fOk = FALSE; // Assume that the function fails
	HANDLE hProcess = NULL, hThread = NULL;
	PWSTR pszLibFileRemote = NULL;

	PFN_CreateRemoteThread pCreateRemoteThread = (PFN_CreateRemoteThread)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "CreateRemoteThread" ) );
	PFN_WriteProcessMemory pWriteProcessMemory = (PFN_WriteProcessMemory)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "WriteProcessMemory" ) );
	PFN_VirtualAllocEx pVirtualAllocEx = (PFN_VirtualAllocEx)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "VirtualAllocEx" ) );
	PFN_VirtualFreeEx pVirtualFreeEx = (PFN_VirtualFreeEx)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "VirtualFreeEx" ) );
	PFN_OpenProcess pOpenProcess = (PFN_OpenProcess)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "OpenProcess" ) );
	
	for(;;){
		// Get a handle for the target process.
		hProcess = pOpenProcess(
			PROCESS_QUERY_INFORMATION |   // Required by Alpha
			PROCESS_CREATE_THREAD     |   // For CreateRemoteThread
			PROCESS_VM_OPERATION      |   // For VirtualAllocEx/VirtualFreeEx
			PROCESS_VM_WRITE,             // For WriteProcessMemory
			FALSE, dwProcessId);
		if (hProcess == NULL) break;

		// Calculate the number of bytes needed for the DLL's pathname
		int cch = 1 + lstrlenW(pszLibFile);
		int cb  = cch * sizeof(WCHAR);

		// Allocate space in the remote process for the pathname
		pszLibFileRemote = (PWSTR)pVirtualAllocEx(hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);
		if (pszLibFileRemote == NULL) break;

		// Copy the DLL's pathname to the remote process's address space
		if (!pWriteProcessMemory(hProcess, pszLibFileRemote, (PVOID) pszLibFile, cb, NULL)) break;

		// Get the real address of LoadLibraryW in Kernel32.dll
		PTHREAD_START_ROUTINE pfnThreadRtn = (PTHREAD_START_ROUTINE)
			GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
		if (pfnThreadRtn == NULL) break;

		// Create a remote thread that calls LoadLibraryW(DLLPathname)
		hThread = pCreateRemoteThread(hProcess, NULL, 0, pfnThreadRtn, pszLibFileRemote, 0, NULL);
		if (hThread == NULL) break;

		// Wait for the remote thread to terminate
		WaitForSingleObject(hThread, INFINITE);

		fOk = TRUE; // Everything executed successfully
		break;
	}
	// Now, we can clean everthing up

	// Free the remote memory that contained the DLL's pathname
	if (pszLibFileRemote != NULL) 
		pVirtualFreeEx(hProcess, pszLibFileRemote, 0, MEM_RELEASE);

	if (hThread  != NULL) CloseHandle(hThread);
	if (hProcess != NULL) CloseHandle(hProcess);
	return(fOk);
}

BOOL WINAPI KInject::InjectLibA(DWORD dwProcessId, PCSTR pszLibFile){
	// Allocate a (stack) buffer for the Unicode version of the pathname
	//PWSTR pszLibFileW = (PWSTR) _alloca((lstrlenA(pszLibFile) + 1) * sizeof(WCHAR));

	PWSTR pszLibFileW = (PWSTR)VirtualAlloc(0, (lstrlenA(pszLibFile) + 1) * sizeof(WCHAR), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	// Convert the ANSI pathname to its Unicode equivalent
	wsprintfW(pszLibFileW, L"%S", pszLibFile);

	// Call the Unicode version of the function to actually do the work.
	BOOL fStatus = InjectLibW(dwProcessId, pszLibFileW);
	VirtualFree(pszLibFileW, 0, MEM_RELEASE);
	return fStatus;
}

//szExe - exe name
//szArg - command line parameters
//szDLL - dll name to inject with full path
int KInject::CreateAndInject2Process(LPCTSTR szExe, LPCTSTR szArgs, LPCTSTR szDLL, LPCTSTR szDir){
	TCHAR	buf1[0x400];
	TCHAR	buf2[0x400];
	STARTUPINFO si={0};
	PROCESS_INFORMATION pi={0};

	si.cb=sizeof(STARTUPINFO);

	lstrcpy(buf1, szExe);
	lstrcat(buf1, TEXT(" "));
	lstrcat(buf1, szArgs);

	if(szDir[0]==0){
		//Create current directory str
		lstrcpy(buf2, szExe);
		for(DWORD i=(DWORD)lstrlen(buf2); i>0; i--){if(buf2[i-1]==TEXT('\\')){buf2[i]=0; break;}}
	}
	else{
		lstrcpy(buf2, szDir);
	}

	PFN_CreateProcessW pCreateProcessW = (PFN_CreateProcessW)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "CreateProcessW" ) );
	if(!pCreateProcessW(0, buf1, 0, 0, 0, CREATE_SUSPENDED, 0, buf2, &si, &pi))
		return -1;

	Inject2(pi.hProcess, pi.hThread);//inject "intruder.dll"
	ResumeThread(pi.hThread);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return 0;
}

BOOL KInject::Inject2Process(DWORD dwPid, LPCTSTR szDLL){
	if(InjectLib(dwPid, szDLL)==TRUE) return 0;
	return -1;
}

void EnableDebugPriv(void)
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;

	HMODULE hAdvapi32 = LoadLibraryA("advapi32.dll");
	PFN_OpenProcessToken pOpenProcessToken = (PFN_OpenProcessToken)(GetProcAddress( hAdvapi32, "OpenProcessToken" ) );
	PFN_LookupPrivilegeValue pLookupPrivVal = (PFN_LookupPrivilegeValue)(GetProcAddress( hAdvapi32, "LookupPrivilegeValueW" ) );
	PFN_AdjustTokenPrivileges pAdjToken = (PFN_AdjustTokenPrivileges)(GetProcAddress( hAdvapi32, "AdjustTokenPrivileges" ) );
	// enable the SeDebugPrivilege
	if ( ! pOpenProcessToken( GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken ) )
		return;

	if ( ! pLookupPrivVal( NULL, SE_DEBUG_NAME, &sedebugnameValue ) )
	{
		CloseHandle( hToken );
		return;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	pAdjToken( hToken, FALSE, &tkp, sizeof tkp, NULL, NULL );
		
	CloseHandle( hToken );
}

