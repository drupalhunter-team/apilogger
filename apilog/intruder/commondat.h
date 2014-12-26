#pragma once
#include <Windows.h>
#include "apilog.h"
#include "khook.h"
#include "klog.h"
#include "init.h"
#include "logger.h"
#include "dbparser.h"

extern LARGE_INTEGER TimerFreq;
extern KLOG *pLog;

extern LARGE_INTEGER TimerStart;
extern SYSTEMTIME    StartTime;


extern SSETTINGS settings;

extern PFN_GetLastError			safe_GetLastError;
extern PFN_SetLastError			safe_SetLastError;
extern PFN_GetCurrentThreadId	safe_GetCurrentThreadId;
extern PFN_EnterCriticalSection	safe_EnterCriticalSection;
extern PFN_LeaveCriticalSection	safe_LeaveCriticalSection;
extern PFN_GetProcessHeap		safe_GetProcessHeap;
extern PFN_HeapAlloc			safe_HeapAlloc;
extern PFN_HeapFree				safe_HeapFree;
extern PFN_VirtualProtectEx		safe_VirtualProtectEx;
extern PFN_CloseHandle			safe_CloseHandle;
extern PFN_WriteFile			safe_WriteFile;
extern PFN_FlushFileBuffers		safe_FlushFileBuffers;
//extern PFN_OutputDebugStringA	safe_OutputDebugStringA;
extern PFN_VirtualAlloc			safe_VirtualAlloc;
extern PFN_VirtualFree			safe_VirtualFree;
extern PFN_wvsprintfA			safe_wvsprintfA;
extern PFN_GetModuleFileNameW	safe_GetModuleFileNameW;
extern PFN_ExitProcess			safe_ExitProcess;
extern PFN_TlsAlloc				safe_TlsAlloc;
extern PFN_TlsFree				safe_TlsFree;
extern PFN_TlsSetValue			safe_TlsSetValue;
extern PFN_TlsGetValue			safe_TlsGetValue;
extern PFN_LdrLoadDll			safe_LdrLoadDll;
extern PFN_QueryPerformanceCounter     safe_QueryPerformanceCounter;

extern DWORD	hIntruder;
extern SFUNCDB*	hookdb;
extern DWORD	dwHooks;
extern DWORD	dwPluginHooks;
extern CRITICAL_SECTION csLog;
extern DWORD	ExeImageBase;
extern DWORD	ExeSizeOfImage;
extern DWORD	dwTlsIndex;
extern DWORD	dwExcludeModules;
extern char**	ppExcludeModules;
extern DWORD	dwIncludeModules;
extern char**	ppIncludeModules;
extern DWORD	StartUpDone;
extern STHREAD *sthreads;
extern CRITICAL_SECTION cs;
extern DWORD	adrExitThread;
