#pragma once


#define PLUGINSDK_VER 0x13

struct SPROXYENTRYSTRUCT;
struct SPROXYEXIT;

typedef DWORD	(__stdcall *PPLUG_BEFORE)(SPROXYENTRYSTRUCT*);
typedef DWORD	(__stdcall *PPLUG_AFTER) (SPROXYEXIT*, DWORD);

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

#pragma pack(push,1)
struct SFUNCTION{
	char*			pName;//function name
	char*			pExtName;//Extended function name
	PPLUG_BEFORE	BeforeFunc;
	PPLUG_AFTER		AfterFunc;
	BYTE			params;//params count
	BYTE			fDumpRegs;
	BYTE			fDumpFpu;
	BYTE			fDumpMMX;
	BYTE			fDumpXMM;
	BYTE			fDumpTacts;
	BYTE			fNoLog;
	BYTE			fEcx;
	BYTE			fEax;
};
#pragma pack(pop)

void	Logger(PCHAR , ...);
void	InitUserPlugin();

//Plugin interface
#pragma pack(push,1)
struct PLUGIN{
	PPLUG_BEFORE	Before;		//Pointer To "Before" Handler
	PPLUG_AFTER		After;		//Pointer To "After"  Handler
};
#pragma pack(pop)

#pragma pack(push,1)
struct PLUGIN_DAT{
	char*			szName;		//Function Name
	PPLUG_BEFORE	Before;		//Pointer To "Before" Handler
	PPLUG_AFTER		After;		//Pointer To "After"  Handler
};
#pragma pack(pop)

typedef void	(__stdcall *PFN_Str2Log)(char *szStr);
typedef DWORD	(__stdcall *PFN_GetUnhookedFuncAddrByName)(char* szFuncName);
typedef DWORD	(__stdcall *PFN_SetHook)(DWORD addr, SFUNCTION* pFuncInfo);
typedef DWORD	(__stdcall *PFN_GetFuncInfoById)(DWORD id, SFUNCTION* pHF);
typedef void	(__stdcall *PFN_SetPluginHandler2All)(PLUGIN* pPlugReg);
typedef	DWORD	(__stdcall *PFN_GetUnhookedFuncAddrById)(DWORD id);


typedef	DWORD (WINAPI *PFN_F0)();
typedef	DWORD (WINAPI *PFN_F1)(DWORD);
typedef	DWORD (WINAPI *PFN_F2)(DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F3)(DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F4)(DWORD, DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F5)(DWORD, DWORD, DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F6)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F7)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F8) (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F9) (DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);
typedef	DWORD (WINAPI *PFN_F10)(DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD);


void stub_0();
void stub_1();
void stub_2();
void stub_3();
void stub_4();
void stub_5();
void stub_6();
void stub_7();
void stub_8();
void stub_9();
void stub_10();

