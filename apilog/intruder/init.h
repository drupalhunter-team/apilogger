#pragma once
#include "logger.h"

struct SFUNCINFO;
struct PLUGIN;

#define GETADDR(hM, func){safe_##func=(PFN_##func)GetProcAddress(hM, #func); if(!safe_##func) FatalError(#func);}

#define GETADDR2(hM, func){\
	safe_##func=(PFN_##func)GetProcAddress(hM, #func);\
	if(!safe_##func) FatalError(#func);\
	safe_##func=(PFN_##func)GetSafeFuncStartOrig(safe_##func);\
	if(!safe_##func) FatalError(#func);\
}


void	copy_file(char *szSrcFile, char *szDstFile, int fEP, int fPatch);
PIMAGE_SECTION_HEADER RvaToSection(PIMAGE_FILE_HEADER pFH, DWORD dwRVA);

int		InitLogger(DWORD hMod);
void	DeInitLogger();
char*	IsAlreadyHooked(DWORD addr);

void	LoadPlugin(char* szPlugin);
void	LoadPlugins();
extern "C" void __stdcall Str2Log(char *s);
extern "C" DWORD __stdcall SetHook(DWORD addr, SFUNCTION* pFuncInfo);
extern "C" DWORD __stdcall GetUnhookedFuncAddrByName(char *szFuncName);
void str2log(PCHAR fmt, ...);

typedef char* (__stdcall *PFN_START_PLUGIN) (DWORD, DWORD);
typedef char* (__stdcall *PFN_REGISTER_FUNC)(PLUGIN *);


//Plugin interface
#pragma pack(push,1)
struct PLUGIN{
	PPLUG_BEFORE	Before;		//Pointer To "Before" Handler
	PPLUG_AFTER		After;		//Pointer To "After"  Handler
};
#pragma pack(pop)

void	RegHandler(char*, PLUGIN*);
//DWORD	GetKernel32Base();
void	GetExeInfo(DWORD hMod, DWORD* SizeOfImage);
void	ReadSettings(DWORD hMod);
DWORD	DetermineProcessStartup();

typedef BOOL (__stdcall *PFN_EnumProcessModules)(HANDLE hProcess,HMODULE* lphModule,DWORD cb,LPDWORD lpcbNeeded);
typedef DWORD (__stdcall *PFN_GetModuleFileNameExA)(HANDLE hProcess,HMODULE hModule,char* lpFilename,DWORD nSize);


DWORD GetFunctionAddresses(SFUNCDB* pFuncDb, DWORD Cnt);
char* StrBufN(char *buf, char *str, int buflen);
void Hooker(DWORD i);
void DumpDb();
void InitSafeFuncAddresses( HMODULE hKernel32, DWORD Flag );


struct KFUNC{
	char* szFunc;
	void* pAddr;
};
