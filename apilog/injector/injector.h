#pragma once

void GetIniPath(TCHAR* buf, DWORD len);
void SetOutFile(HWND hDlg, TCHAR* szEXEFile);
void SavePath(HWND hDlg);
LRESULT CALLBACK DlgSettings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void SaveSettings(HWND hDlg);


typedef BOOL (__stdcall *PFN_CreateProcessW)(
	LPCTSTR lpApplicationName,
	LPTSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCTSTR lpCurrentDirectory,
	LPSTARTUPINFO lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
				   );



typedef HANDLE (__stdcall *PFN_CreateRemoteThread)(
						  HANDLE hProcess,
						  LPSECURITY_ATTRIBUTES lpThreadAttributes,
						  SIZE_T dwStackSize,
						  LPTHREAD_START_ROUTINE lpStartAddress,
						  LPVOID lpParameter,
						  DWORD dwCreationFlags,
						  LPDWORD lpThreadId
						  );


typedef BOOL (__stdcall *PFN_WriteProcessMemory)(
						HANDLE hProcess,
						LPVOID lpBaseAddress,
						LPCVOID lpBuffer,
						SIZE_T nSize,
						SIZE_T* lpNumberOfBytesWritten
						);


typedef LPVOID (__stdcall *PFN_VirtualAllocEx)(
					  HANDLE hProcess,
					  LPVOID lpAddress,
					  SIZE_T dwSize,
					  DWORD flAllocationType,
					  DWORD flProtect
					  );


typedef BOOL (__stdcall *PFN_VirtualFreeEx)(
				   HANDLE hProcess,
				   LPVOID lpAddress,
				   SIZE_T dwSize,
				   DWORD dwFreeType
				   );


typedef HANDLE (__stdcall *PFN_OpenProcess)(
				   DWORD dwDesiredAccess,
				   BOOL bInheritHandle,
				   DWORD dwProcessId
				   );


typedef DWORD (__stdcall *PFN_QueueUserAPC)(
				   PAPCFUNC pfnAPC,
				   HANDLE hThread,
				   ULONG_PTR dwData
				   );

typedef BOOL (__stdcall *PFN_OpenProcessToken)(
					  HANDLE ProcessHandle,
					  DWORD DesiredAccess,
					  PHANDLE TokenHandle
					  );



typedef BOOL (__stdcall *PFN_LookupPrivilegeValue)(
						  LPCTSTR lpSystemName,
						  LPCTSTR lpName,
						  PLUID lpLuid
						  );


typedef BOOL (__stdcall *PFN_AdjustTokenPrivileges)(
						   HANDLE TokenHandle,
						   BOOL DisableAllPrivileges,
						   PTOKEN_PRIVILEGES NewState,
						   DWORD BufferLength,
						   PTOKEN_PRIVILEGES PreviousState,
						   PDWORD ReturnLength
						   );


typedef BOOL (__stdcall *PFN_EnumProcesses)(
				   DWORD* lpidProcess,
				   DWORD cb,
				   DWORD* cbNeeded
				   );


typedef DWORD (__stdcall *PFN_GetModuleBaseName)(
						HANDLE hProcess,
						HMODULE hModule,
						LPTSTR lpBaseName,
						DWORD nSize
						);



typedef DWORD (__stdcall *PFN_GetModuleFileNameEx)(
						  HANDLE hProcess,
						  HMODULE hModule,
						  LPTSTR lpFilename,
						  DWORD nSize
						  );


typedef HINSTANCE (__stdcall *PFN_ShellExecute)(HWND hwnd,
					   LPCTSTR lpOperation,
					   LPCTSTR lpFile,
					   LPCTSTR lpParameters,
					   LPCTSTR lpDirectory,
					   INT nShowCmd
					   );
