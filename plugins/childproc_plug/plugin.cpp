// plugin.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include "plugin.h"
#include "kinject.h"
#pragma comment(lib, "shlwapi.lib")

char							szPluginName[] = "ChildProcess Logger Plugin";
HANDLE							hDLL = 0;
PFN_Str2Log						Str2Log = 0;
PFN_SetHook						SetHook = 0;
PFN_GetUnhookedFuncAddrByName	GetUnhookedFuncAddrByName = 0;
PFN_GetFuncInfoById				GetFuncInfoById = 0;
PFN_SetPluginHandler2All		SetPluginHandler2All = 0;
PFN_GetUnhookedFuncAddrById		GetUnhookedFuncAddrById = 0;


//DWORD __stdcall before_XXX(SPROXYENTRYSTRUCT* pEntry);
//DWORD __stdcall after_XXX(SPROXYEXIT* pExit, DWORD RetVal);

void InitUserPlugin(){
	//Add You Initialization Code Here
}

DWORD __stdcall before_CreateProcessA(SPROXYENTRYSTRUCT* pEntry){
	DWORD retv;
	if(StrStrIA((char*)pEntry->parameters[1], "stdrt")){
			retv = ((PFN_F10)GetUnhookedFuncAddrById(pEntry->funcid))(
			pEntry->parameters[0],	//LPCTSTR lpApplicationName
			pEntry->parameters[1],	//LPTSTR lpCommandLine
			pEntry->parameters[2],	//LPSECURITY_ATTRIBUTES lpProcessAttributes
			pEntry->parameters[3],	//LPSECURITY_ATTRIBUTES lpThreadAttributes
			pEntry->parameters[4],	//BOOL bInheritHandles
			pEntry->parameters[5] | CREATE_SUSPENDED,	//DWORD dwCreationFlags
			pEntry->parameters[6],	//LPVOID lpEnvironment
			pEntry->parameters[7],	//LPCTSTR lpCurrentDirectory
			pEntry->parameters[8],	//LPSTARTUPINFO lpStartupInfo
			pEntry->parameters[9]	//LPPROCESS_INFORMATION lpProcessInformation
			);


		Str2Log("Target Detected\r\n");
		LPPROCESS_INFORMATION ppi = (LPPROCESS_INFORMATION)pEntry->parameters[9];
		KInject inj;
		inj.Inject2(ppi->hProcess,  ppi->hThread);
		Str2Log("Inject OK\r\n");
		ResumeThread(ppi->hThread);
		Str2Log("Target Detected\r\n");
	}
	else{
			retv = ((PFN_F10)GetUnhookedFuncAddrById(pEntry->funcid))(
			pEntry->parameters[0],	//LPCTSTR lpApplicationName
			pEntry->parameters[1],	//LPTSTR lpCommandLine
			pEntry->parameters[2],	//LPSECURITY_ATTRIBUTES lpProcessAttributes
			pEntry->parameters[3],	//LPSECURITY_ATTRIBUTES lpThreadAttributes
			pEntry->parameters[4],	//BOOL bInheritHandles
			pEntry->parameters[5],	//DWORD dwCreationFlags
			pEntry->parameters[6],	//LPVOID lpEnvironment
			pEntry->parameters[7],	//LPCTSTR lpCurrentDirectory
			pEntry->parameters[8],	//LPSTARTUPINFO lpStartupInfo
			pEntry->parameters[9]	//LPPROCESS_INFORMATION lpProcessInformation
			);
	}
	pEntry->eax=(DWORD)retv;
	return (DWORD)stub_10;
}

DWORD __stdcall before_CreateProcessW(SPROXYENTRYSTRUCT* pEntry){
	HRESULT retv = ((PFN_F10)GetUnhookedFuncAddrById(pEntry->funcid))(
		pEntry->parameters[0],
		pEntry->parameters[1],
		pEntry->parameters[2],
		pEntry->parameters[3],
		pEntry->parameters[4],
		pEntry->parameters[5],
		pEntry->parameters[6],
		pEntry->parameters[7],
		pEntry->parameters[8],
		pEntry->parameters[9]
		);

	pEntry->eax=(DWORD)retv;
	return (DWORD)stub_10;
}

PLUGIN_DAT plugins[]=
{	
	{	
		"CreateProcessA",
		before_CreateProcessA,
		0
	},
	{
		"CreateProcessW",
		before_CreateProcessW,
		0
	}
};

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	hDLL=hModule;
	return TRUE;
}

//------------------------
//Exported Functions
//------------------------
extern "C"  char* __stdcall StartPlugin(DWORD hIntruder, DWORD dwVer){
	if(dwVer != PLUGINSDK_VER) return 0;//Versions mismatch. Can't init

	Str2Log=(PFN_Str2Log)GetProcAddress((HMODULE)hIntruder, "Str2Log");
	SetHook=(PFN_SetHook)GetProcAddress((HMODULE)hIntruder, "SetHook");
	GetUnhookedFuncAddrByName = (PFN_GetUnhookedFuncAddrByName)GetProcAddress((HMODULE)hIntruder, "GetUnhookedFuncAddrByName");
	GetFuncInfoById = (PFN_GetFuncInfoById)GetProcAddress((HMODULE)hIntruder, "GetFuncInfoById");
	SetPluginHandler2All = (PFN_SetPluginHandler2All)GetProcAddress((HMODULE)hIntruder, "SetPluginHandler2All");
	GetUnhookedFuncAddrById = (PFN_GetUnhookedFuncAddrById)GetProcAddress((HMODULE)hIntruder, "GetUnhookedFuncAddrById");

	InitUserPlugin();
	return szPluginName;
}

extern "C"  char* __stdcall RegisterHandler(PLUGIN *plug){
	static DWORD id=0;

	if(id<(sizeof(plugins)/sizeof(PLUGIN_DAT))){
		id++;
		plug->Before = plugins[id-1].Before;
		plug->After	 = plugins[id-1].After;
		return	plugins[id-1].szName;
	}
	return 0;
}

//Helper function
void Logger(PCHAR fmt, ...){
	char buf[0x100];

	va_list ap;
	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	Str2Log(buf);
	va_end(ap);
}

void __declspec(naked) stub_0(){
	__asm{
		retn    
	}
}

void __declspec(naked) stub_1(){
	__asm{
		retn    4
	}
}
void __declspec(naked) stub_2(){
	__asm{
		retn    8
	}
}
void __declspec(naked) stub_3(){
	__asm{
		retn    0Ch
	}
}
void __declspec(naked) stub_4(){
	__asm{
		retn    10h
	}
}
void __declspec(naked) stub_5(){
	__asm{
		retn    14h
	}
}
void __declspec(naked) stub_6(){
	__asm{
		retn    18h
	}
}
void __declspec(naked) stub_7(){
	__asm{
		retn    1Ch
	}
}
void __declspec(naked) stub_8(){
	__asm{
		retn    20h
	}
}
void __declspec(naked) stub_9(){
	__asm{
		retn    24h
	}
}
void __declspec(naked) stub_10(){
	__asm{
		retn    28h
	}
}
