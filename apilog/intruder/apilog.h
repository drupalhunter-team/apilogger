#pragma once

class  KHOOK;
struct KROUTINE;
struct STHREAD;

#define PLUGINSDK_VER 0x13

#define MAX_DEPTH	16*1024
#define MAX_THREADS 16

enum{
	MODE_TLS_WAITEXE = 3,
	MODE_TLS_NOTWAIT = 2,
	MODE_SAFE = 1,
	MODE_LEGACY = 0
};

#pragma pack(push,1)
struct KUNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
};
#pragma pack(pop)

extern "C" DWORD  __stdcall FpuFLtoA(PBYTE lpSrc, PBYTE lpDecimal, PBYTE lpDest, DWORD uID);

typedef DWORD	(__stdcall *PFN_GetLastError)(void);
typedef void	(__stdcall *PFN_SetLastError)(DWORD);
typedef DWORD	(__stdcall *PFN_GetCurrentThreadId)(void);
typedef void	(__stdcall *PFN_EnterCriticalSection)(LPCRITICAL_SECTION);
typedef void	(__stdcall *PFN_LeaveCriticalSection)(LPCRITICAL_SECTION);
typedef HANDLE	(__stdcall *PFN_GetProcessHeap)(void);
typedef LPVOID	(__stdcall *PFN_HeapAlloc)(HANDLE, DWORD, SIZE_T);
typedef BOOL	(__stdcall *PFN_HeapFree)(HANDLE, DWORD, LPVOID);
typedef BOOL	(__stdcall *PFN_VirtualProtectEx)(HANDLE, LPVOID, SIZE_T, DWORD, PDWORD);
typedef BOOL	(__stdcall *PFN_FlushInstructionCache)(HANDLE, LPCVOID, SIZE_T);
typedef BOOL	(__stdcall *PFN_CloseHandle)(HANDLE);
typedef BOOL	(__stdcall *PFN_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
typedef BOOL	(__stdcall *PFN_FlushFileBuffers)(HANDLE);
typedef void	(__stdcall *PFN_OutputDebugStringA)(char *);
typedef LPVOID	(__stdcall *PFN_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
typedef BOOL	(__stdcall *PFN_VirtualFree)(LPVOID, SIZE_T, DWORD);
typedef int		(__stdcall *PFN_wvsprintfA)(char *, char *, va_list);
typedef DWORD	(__stdcall *PFN_GetModuleFileNameW)(HMODULE, WORD *, DWORD);
typedef void	(__stdcall *PFN_ExitProcess)(UINT);
typedef	DWORD	(__stdcall *PFN_TlsAlloc)(void);
typedef BOOL	(__stdcall *PFN_TlsFree)(DWORD dwTlsIndex);
typedef	LPVOID	(__stdcall *PFN_TlsGetValue)(DWORD dwTlsIndex);
typedef BOOL	(__stdcall *PFN_TlsSetValue)(DWORD dwTlsIndex, LPVOID lpTlsValue);
//v1.5
typedef DWORD	(__stdcall *PFN_LdrLoadDll)(WORD* dwTlsIndex, DWORD* pError, KUNICODE_STRING*, DWORD* pResInst );
typedef BOOL    (__stdcall *PFN_QueryPerformanceCounter)(LARGE_INTEGER *lpPerformanceCount);


//Antivirii
typedef BOOL    (__stdcall *PFN_VirtualProtectEx)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
typedef UINT    (__stdcall *PFN_GetSystemDirectoryA)(char* lpBuffer, UINT uSize);
typedef DWORD   (__stdcall *PFN_GetTempPathA)(DWORD nBufferLength, char* lpBuffer);
typedef HANDLE  (__stdcall *PFN_FindFirstFileA)(char* lpFileName, LPWIN32_FIND_DATA lpFindFileData);
typedef HANDLE  (__stdcall *PFN_CreateFileA)(char* lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
typedef HMODULE (__stdcall *PFN_LoadLibraryA)( char* lpFileName );






void*	MemAlloc(DWORD size);
void	MemFree(void *p);
void*	MemAllocTrue(DWORD size);
void	MemFreeTrue(void *p);


__declspec(noreturn) void FatalError(char *msg);


#pragma pack(push,1)
struct SSETTINGS{
	char	szDBFile[260];
	char	szOutFile[260];
	DWORD	strminlen;
	DWORD	strmaxlen;
	DWORD	dwPluginHooks;
	BYTE	fLogTID;
	BYTE	fOnlyFirst;
	BYTE	fExtFuncNames;
	BYTE	fLogOnlyExeCalls;
	BYTE	fDisableLog;
	BYTE	dwMode;
	//v1.3
	BYTE	PELoader;
	BYTE	DisableKernel32Load;
	//v1.5
	BYTE    ForceDllLoad;
	BYTE    DumpDb;
	BYTE    Profiler;
	//v1.6
	BYTE    Time;
};
#pragma pack(pop)


#pragma pack(push,1)
struct SPROXYENTRYSTRUCT{
	DWORD	edi;
	DWORD	esi;
	DWORD	ebp;
	DWORD	esp;
	DWORD	ebx;
	DWORD	edx;
	DWORD	ecx;
	DWORD	eax;
	DWORD	eflags;
	DWORD	funcid;
	DWORD	retaddr;
	DWORD	parameters[32];
};
#pragma pack(pop)


#pragma pack(push,1)
struct SPROXYEXIT{
	DWORD result;
};
#pragma pack(pop)


void ProxyProlog(void);
void __stdcall ProxyEntry(SPROXYENTRYSTRUCT *pInfo, DWORD dwEnterTacts);

void ProxyEpilog(void);
void __stdcall ProxyExit(SPROXYEXIT* pExitInfo, DWORD dwLeaveTacts);
KROUTINE* Push();
KROUTINE* LookupStack();
void Pop();

void ProxyPrologSafe(void);
void __stdcall ProxyEntrySafe(SPROXYENTRYSTRUCT *pInfo, DWORD dwEnterTacts);
void Dump();
LPVOID MyTlsGetValue(DWORD dwTlsIndex);
