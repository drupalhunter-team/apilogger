
#include "stdafx.h"
#include <Windows.h>
#include <WinNT.h>

#include "apilog.h"
#include "khook.h"
#include "klog.h"
#include "init.h"
#include "logger.h"
#include "dbparser.h"
#include "commondat.h"


extern HMODULE g_hKernel32;


//Code from Packers part 1
PIMAGE_SECTION_HEADER RvaToSection(PIMAGE_FILE_HEADER pFH, DWORD dwRVA){
	UINT i=0;
	IMAGE_SECTION_HEADER *pSH=0;
	pSH=(PIMAGE_SECTION_HEADER)((DWORD)(pFH+1)+pFH->SizeOfOptionalHeader);

	for(i=0; i<pFH->NumberOfSections; i++){
		if(dwRVA>=pSH->VirtualAddress && dwRVA < pSH->VirtualAddress + pSH->Misc.VirtualSize) return pSH;
		++pSH;
	}
	return 0;
}


void copy_file(char *szSrcFile, char *szDstFile, int fEP, int fPatch){
	DWORD dwFileSize=0, dwTemp=0, i=0;
	BYTE *pData=0;
	WIN32_FIND_DATA fd={0};
	HANDLE hFile=0;

	PFN_FindFirstFileA pFindFirstFileA = (PFN_FindFirstFileA)( GetProcAddress( g_hKernel32, "FindFirstFileA" ) );

	if(pFindFirstFileA(szDstFile, &fd)==INVALID_HANDLE_VALUE){//not create. if exist
		PFN_CreateFileA pCreateFileA = (PFN_CreateFileA)( GetProcAddress( g_hKernel32, "CreateFileA" ) );

		hFile=pCreateFileA(szSrcFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if(hFile==INVALID_HANDLE_VALUE) FatalError("Can't open file for read");

		dwFileSize=GetFileSize(hFile, 0);
		pData=(BYTE*)VirtualAlloc(0, dwFileSize, MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
		if(!pData) FatalError("Malloc error");
		ReadFile(hFile, pData, dwFileSize, &dwTemp, 0);
		CloseHandle(hFile);

		hFile=pCreateFileA(szDstFile, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(hFile==INVALID_HANDLE_VALUE) FatalError("Can't open file for writing");
		WriteFile(hFile, pData, dwFileSize, &dwTemp, 0);
		CloseHandle(hFile);
		VirtualFree(pData, 0, MEM_RELEASE|MEM_DECOMMIT);

	}
}


int InitLogger(DWORD hMod){
	char szBuffer[MAX_PATH];
	char szDstBuf[MAX_PATH];

	char szKERNEL32[]  = "kernel32.dll";
	char szKERNELBASE[]= "kernelbase.dll";

	char* szKERN = szKERNEL32;
	OSVERSIONINFO winver = {0};
	winver.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
	GetVersionEx( &winver );
	if( winver.dwBuildNumber >= 7000 ){// If Win7/Serv2008 -> use kernelbase.dll instead of kernel32.dll
		szKERN = szKERNELBASE;
	}
	else{
		szKERN = szKERNEL32;
	}


	HMODULE hUser32 = 0;//kernelbase.dll
	g_hKernel32 = (HMODULE)GetModuleHandle( szKERN );
	if( !g_hKernel32 ){
		g_hKernel32 = LoadLibrary( szKERN );
		if( g_hKernel32==0 )
			FatalError( szKERN );
	}

	adrExitThread = (DWORD)GetProcAddress( g_hKernel32, "ExitThread" );

	StartUpDone = DetermineProcessStartup();

	hIntruder = hMod;
	dwTlsIndex = TlsAlloc();

	GetExeInfo((DWORD)GetModuleHandle(0), &ExeSizeOfImage);
	ExeImageBase = (DWORD)GetModuleHandle(0);

	ReadSettings(hMod);
	PFN_GetSystemDirectoryA pGetSystemDirectoryA = (PFN_GetSystemDirectoryA)(GetProcAddress( g_hKernel32, "GetSystemDirectoryA" ) );
	pGetSystemDirectoryA(szBuffer, MAX_PATH);
	strcat(szBuffer, "\\user32.dll");
	hUser32 = GetModuleHandle(szBuffer);
	if( !hUser32 ){
		hUser32=LoadLibrary(szBuffer);
		if(!hUser32) FatalError("Can't load user32.dll");
	}

	if(settings.DisableKernel32Load){
		InitSafeFuncAddresses( g_hKernel32, 1 );
		safe_wvsprintfA = (PFN_wvsprintfA)GetSafeFuncStartOrig( GetProcAddress(hUser32, "wvsprintfA") );
	}
	else{
		PFN_GetSystemDirectoryA pGetSystemDirectoryA = (PFN_GetSystemDirectoryA)(GetProcAddress( g_hKernel32, "GetSystemDirectoryA" ) );
		PFN_GetTempPathA pGetTempPathA = (PFN_GetTempPathA)(GetProcAddress( g_hKernel32, "GetTempPathA" ) );
		pGetSystemDirectoryA(szBuffer, MAX_PATH);
		pGetTempPathA(MAX_PATH, szDstBuf);
		strcat(szBuffer, "\\kernel32.dll");//????????????????????????????????????
		strcat(szDstBuf, "krn32l1g.dll");

		copy_file(szBuffer, szDstBuf, 0, 0);
		PFN_LoadLibraryA pLoadLibraryA = (PFN_LoadLibraryA)(GetProcAddress( g_hKernel32, "LoadLibraryA" ) );
		HMODULE hKernel32_1 = pLoadLibraryA( szDstBuf );
		if(!hKernel32_1){
			FatalError("Can't load krn32l1g.dll");
		}
		InitSafeFuncAddresses( hKernel32_1, 0 );
		safe_wvsprintfA = (PFN_wvsprintfA)GetSafeFuncStart(GetProcAddress(hUser32, "wvsprintfA"));
	}

	if(settings.dwMode == MODE_TLS_NOTWAIT || settings.dwMode == MODE_SAFE || settings.dwMode == MODE_LEGACY){
		StartUpDone = 1;
	}

	InitializeCriticalSection(&csLog);
	InitializeCriticalSection(&cs);

	if(settings.dwMode == MODE_LEGACY){
		sthreads = (STHREAD*)VirtualAlloc(0, MAX_THREADS * sizeof(STHREAD), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	}

	int err=0;
	DWORD Flags=0;
	if(!settings.fDisableLog)	Flags|=1;	// Log on/off flag

	pLog = new (settings.szOutFile, Flags, &err) KLOG;
	if(!pLog){
		MessageBox(0, GetLogErrorText(err), 0, MB_ICONERROR|MB_TOPMOST);
		return -1;
	}
	
	str2log("API Logger v1.9\r\n(C)2004-2012 black_ninja\r\n\r\n");
	pLog->WriteTimeStr();
	str2log("\r\n");

	TimerFreq.QuadPart = 0;
	QueryPerformanceFrequency( &TimerFreq );
	QueryPerformanceCounter( &TimerStart );
	GetLocalTime( &StartTime );
	StartTime.wMilliseconds = 0;


	if(settings.Profiler){
		str2log( "QPC Frequency=%u tics/sec\r\n", TimerFreq.QuadPart );
	}

	hookdb = ParseDB(settings.szDBFile, &dwHooks);
	if(!hookdb){
		return 0;
	}

	DWORD ReadyToHook = GetFunctionAddresses( hookdb, dwHooks );
	str2log("\r\nFunctions ready to hook: %d\r\nTotal function in DB   : %d\r\n", ReadyToHook, dwHooks );

	if(settings.DumpDb)
		DumpDb();


	LoadPlugins();

	//Hook functions
	//dwHook == Parsed from DB functions count
	for(DWORD i=0; i<dwHooks; i++){
		char* szPrevName = IsAlreadyHooked((DWORD)hookdb[i].FuncAddr);
		if(szPrevName){
			str2log("ERROR: Function %s already hooked. Hooker function: %s\r\n", hookdb[i].Func.pName, szPrevName);
		}
		else if( hookdb[i].FuncAddr ){//If function address found

			if(settings.dwMode == MODE_SAFE){
				hookdb[i].pHook = new ((LPCVOID)hookdb[i].FuncAddr, (LPCVOID)ProxyPrologSafe, &err, i) KHOOK;
			}
			else{
				hookdb[i].pHook = new ((LPCVOID)hookdb[i].FuncAddr, (LPCVOID)ProxyProlog, &err, i) KHOOK;
			}

			if(!hookdb[i].pHook){
				str2log("ERROR: Can't set hook to %s : %s\r\n", hookdb[i].Func.pName, GetHookErrorText(err));
			}
		}
	}

	if(dwExcludeModules && !dwIncludeModules){
		str2log("Exclude modules: ");
		i = 0;
		if(dwExcludeModules > 1){
			for(i = 0; i < dwExcludeModules - 1; i++){
				str2log("%s, ", ppExcludeModules[i]);
			}
		}
		str2log("%s\r\n", ppExcludeModules[i]);
	}
	else if(dwIncludeModules && !dwExcludeModules){
		str2log("Include modules: ");
		i = 0;
		if(dwIncludeModules > 1){
			for(i = 0; i < dwIncludeModules - 1; i++){
				str2log("%s, ", ppIncludeModules[i]);
			}
		}
		str2log("%s\r\n", ppIncludeModules[i]);
	}
	else if(dwIncludeModules != 0 && dwExcludeModules != 0){
		str2log("ERROR: Include and Exclude Modules conflict. Change settings in settings.ini\r\n");
		dwIncludeModules=0;
		dwExcludeModules=0;
	}

	str2log("\r\nLOG START\r\n\r\n");
	return 0;
}

char* IsAlreadyHooked(DWORD addr){
	for(DWORD i=0; i<dwHooks; i++){
		if(hookdb[i].pHook){
			if((DWORD)hookdb[i].pHook->addr == addr) return hookdb[i].Func.pName;
		}
	}
	return 0;
}


void PrintModules(){
	HMODULE hMods[1024];
	HANDLE hProcess;
	DWORD cbNeeded;
	unsigned int i;
	char szModName[MAX_PATH];

	HMODULE hPSAPI = LoadLibraryA("psapi.dll");
	PFN_EnumProcessModules aEnumProcessModules = 0;
	PFN_GetModuleFileNameExA aGetModuleFileNameExA = 0;
	if(hPSAPI){
		aEnumProcessModules  = (PFN_EnumProcessModules)GetProcAddress(hPSAPI, "EnumProcessModules");
		aGetModuleFileNameExA= (PFN_GetModuleFileNameExA)GetProcAddress(hPSAPI, "GetModuleFileNameExA");
	}

	if(!hPSAPI || !aEnumProcessModules || !aGetModuleFileNameExA){
		str2log("\r\n\r\npsapi.dll error\r\n\r\n");
	}
	else{
		str2log("\r\nLoaded Modules List\r\n");
		hProcess = (HANDLE)(-1);
		if(aEnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)){
			for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ ){
				if ( aGetModuleFileNameExA( hProcess, hMods[i], szModName,sizeof(szModName))){
					str2log("%08X %s\r\n", hMods[i], szModName);
				}
			}
		}
	}

}

void DeInitLogger(){
	PrintModules();// DLLs List

	str2log("\r\n\r\nLOG END\r\n\r\n");
	delete pLog;
}


extern "C" DWORD __stdcall GetUnhookedFuncAddrByName(char *szFuncName){
	DWORD res=0;
	for(DWORD i=0; i<dwHooks; i++){
		if(!strcmp(hookdb[i].Func.pName, szFuncName) && hookdb[i].pHook){
			res = (DWORD)hookdb[i].pHook->exec_buf;
			break;
		}
	}
	return res;
}


//Set hook to function from user plugin
//Not thread safe yet
extern "C" DWORD __stdcall SetHook(DWORD addr, SFUNCTION* pFunc){
	int err;
	if( addr==0 ){
		str2log("ERROR: Can't set hook to %s. Zero address\r\n", pFunc->pName );
		return -3;//Can't set hook
	}


	if(dwPluginHooks >= settings.dwPluginHooks){
		str2log("ERROR: Too many plugin hooks. Increase PluginHooks in settings.ini\r\n");
		return -1;	//Can't set hook
	}

	char* szStr = IsAlreadyHooked(addr);
	if(szStr){
		str2log("ERROR: Function %s already hooked. Hooker function %s\r\n", pFunc->pName, szStr);
		return -2;	//Already hooked
	}

	if(settings.Profiler){
		pFunc->fDumpTacts = 1;
	}

	hookdb[dwHooks].Func = *pFunc;
	
	hookdb[dwHooks].FuncAddr = addr;
	if(settings.dwMode == MODE_SAFE){
		hookdb[dwHooks].pHook = new ((LPCVOID)hookdb[dwHooks].FuncAddr, (LPCVOID)ProxyPrologSafe, &err, dwHooks) KHOOK;
	}
	else{
		hookdb[dwHooks].pHook = new ((LPCVOID)hookdb[dwHooks].FuncAddr, (LPCVOID)ProxyProlog, &err, dwHooks) KHOOK;
	}

	if(!hookdb[dwHooks].pHook){
		str2log("ERROR: Can't set hook to %s : %s\r\n", pFunc->pName, GetHookErrorText(err));
		return -3;//Can't set hook
	}
	dwPluginHooks++;
	dwHooks++;
	
	return 0;//ok
}

extern "C" void __stdcall Str2Log(char *s){
	safe_EnterCriticalSection(&csLog);

	pLog->Output(s);

	safe_LeaveCriticalSection(&csLog);
}


void str2log(PCHAR fmt, ...){
	char buffer[1024];

	safe_EnterCriticalSection(&csLog);

	va_list ap;
	va_start(ap, fmt);
	safe_wvsprintfA(buffer, fmt, ap);
	pLog->Output(buffer);
	va_end(ap);

	safe_LeaveCriticalSection(&csLog);
}


void LoadPlugins(){
	char szBuffer[260];

	GetModuleFileName((HMODULE)hIntruder, szBuffer, MAX_PATH);
	for(DWORD i=(DWORD)strlen(szBuffer); i>0; i--){if(szBuffer[i-1]=='\\'){szBuffer[i]=0; break;}}
	strcat(szBuffer, "plugin.dll");
	LoadPlugin(szBuffer);
}

void LoadPlugin(char* szPlugin){
	char		*szPlugInternalName=0;
	PLUGIN		plugin;

	HINSTANCE hPlugin = LoadLibrary(szPlugin);
	if(hPlugin==0) return;

	PFN_START_PLUGIN StartPlugin=(PFN_START_PLUGIN)GetProcAddress(hPlugin, "StartPlugin");
	if(!StartPlugin){str2log("ERROR: StartPlugin export not found in %s\r\n", szPlugin); return;}

	szPlugInternalName=StartPlugin(hIntruder, PLUGINSDK_VER);
	if(!szPlugInternalName){
		str2log("ERROR: Plugin Version Error: %s\r\n", szPlugin);
	}
	else{
		PFN_REGISTER_FUNC	RegisterHandler=(PFN_REGISTER_FUNC)GetProcAddress(hPlugin, "RegisterHandler");
		if(!RegisterHandler) {str2log("ERROR: RegisterHandler export not found in %s\r\n", szPlugin); return;}

		str2log("Plugin: \"%s\"\r\n------------------------------\r\n", szPlugInternalName);
		
		//Set all plugin handled functions
		while(1){
			ZeroMemory(&plugin, sizeof(plugin));
			char *szFuncName=RegisterHandler(&plugin);
			if(!szFuncName) break;

			str2log("Set to \"%s\"   ", szFuncName);

			RegHandler(szFuncName, &plugin);
		}
		str2log("------------------------------\r\n\r\n");
	}
}

void RegHandler(char* szFuncName, PLUGIN* pPlugReg){

	for(DWORD i=0; i<dwHooks; i++){
		if(!strcmp(hookdb[i].Func.pName, szFuncName)){
			if(hookdb[i].Func.BeforeFunc || hookdb[i].Func.AfterFunc){
				str2log("ERROR: Plugins collisions at function\r\n");
				return;
			}
			else{
				hookdb[i].Func.BeforeFunc = pPlugReg->Before;
				hookdb[i].Func.AfterFunc  = pPlugReg->After;
				str2log("ok\r\n");
				return;
			}
		}
	}
	str2log("ERROR: Function not found in DB\r\n");
	return;
}

void GetExeInfo(DWORD hMod, DWORD* SizeOfImage){
	BYTE* lpData=(BYTE*)hMod;
	DWORD e_lfanew=*(DWORD*)&lpData[0x3C];
	PIMAGE_FILE_HEADER pFH=(PIMAGE_FILE_HEADER)(lpData + e_lfanew + 4);
	PIMAGE_SECTION_HEADER pSH=(PIMAGE_SECTION_HEADER)(lpData + e_lfanew + 0x18 + pFH->SizeOfOptionalHeader);

	PIMAGE_OPTIONAL_HEADER32 pOH=(PIMAGE_OPTIONAL_HEADER32)(lpData+e_lfanew+0x18);
	*SizeOfImage = pOH->SizeOfImage;
}


extern "C" DWORD __stdcall GetFuncInfoById(DWORD id, SFUNCTION* pHF){
	if(id >= dwHooks) return dwHooks;

	//pHF = &hookdb[id].Func;
	memcpy( pHF, &hookdb[id].Func, sizeof(SFUNCTION) );
	return 0;
}


extern "C" DWORD __stdcall GetUnhookedFuncAddrById(DWORD id){
	if(id >= dwHooks) return 0;

	return (DWORD)hookdb[id].pHook->exec_buf;
}

extern "C" void __stdcall SetPluginHandler2All(PLUGIN* pPlugReg){
	for(DWORD i=0; i<dwHooks; i++){
		if(pPlugReg->Before && !hookdb[i].Func.BeforeFunc){
			hookdb[i].Func.BeforeFunc = pPlugReg->Before;
		}

		if(pPlugReg->After && !hookdb[i].Func.AfterFunc){
			hookdb[i].Func.AfterFunc = pPlugReg->After;
		}
	}
}


DWORD DetermineProcessStartup(){
	FILETIME ct, t;
	SYSTEMTIME t1, t2;

	GetSystemTime(&t1);
	if(!GetProcessTimes((HANDLE)(-1), &ct, &t, &t, &t)) return 0;
	if(!FileTimeToSystemTime(&ct, &t2)) return 0;

	if(t1.wYear>t2.wYear) return 1;
	if(t1.wMonth>t2.wMonth) return 1;
	if(t1.wDay>t2.wDay) return 1;
	if(t1.wHour>t2.wHour) return 1;
	if(t1.wMinute>t2.wMinute) return 1;
	if(t1.wSecond - t2.wSecond > 3) return 1;

	return 0;
}


DWORD __stdcall StubLdrLoadDll(WORD* a1, DWORD* pError, KUNICODE_STRING* pUnicode, DWORD* pResInst ){
	DWORD xxx;
	char* pAscii = (char*)MemAlloc( pUnicode->MaximumLength+1 );
	Unicode2Ascii( pUnicode->Buffer, (BYTE*)pAscii, pUnicode->Length );

	//Call LdrLoadDll
	xxx = safe_LdrLoadDll( a1, pError, pUnicode, pResInst );

	if( *pResInst != 0 ){//DLL Loaded
		for(DWORD i=0; i<dwHooks; i++){
			if( hookdb[i].FuncAddr == 0 && hookdb[i].HookType != ABSOLUTE_ADDR ){
				if( StrBufN(pAscii, hookdb[i].szDllName, strlen(pAscii) ) ){
					if( hookdb[i].HookType == EXPORT_NAME ){
						hookdb[i].FuncAddr = (DWORD)GetProcAddress( (HMODULE)*pResInst, hookdb[i].Func.pName );
					}
					else if( hookdb[i].HookType == EXPORT_ORDINAL ){
						hookdb[i].FuncAddr = (DWORD)GetProcAddress( (HMODULE)*pResInst, (LPCSTR)hookdb[i].Stuff );
					}
					else if( hookdb[i].HookType == RVA_ADDR ){
						hookdb[i].FuncAddr = *pResInst + hookdb[i].Stuff;
					}
					Hooker(i);
					str2log( "Function \"%s\" from %s hooked\r\n", hookdb[i].Func.pName, hookdb[i].szDllName );
				}
			}
		}
	}
	MemFree( pAscii );
	return xxx;
}

DWORD  GetFunctionAddresses( SFUNCDB* pFuncDb, DWORD dwHooks ){
	DWORD dwReady = 0;
	for(DWORD i = 0; i < dwHooks; i++){
		if( pFuncDb[i].HookType == ABSOLUTE_ADDR ){
			pFuncDb[i].FuncAddr = pFuncDb[i].Stuff;
			dwReady++;
		}
		else if( pFuncDb[i].HookType == EXPORT_NAME ){
			HMODULE hDLL = GetModuleHandle( pFuncDb[i].szDllName );
			if( hDLL != 0 ){
				pFuncDb[i].FuncAddr = (DWORD)GetProcAddress( hDLL, pFuncDb[i].Func.pName );

				if( pFuncDb[i].FuncAddr ){
					dwReady++;
				}
				else{//Error in GetProcAddress. Get error code
					str2log( "ExportByName failed. DLL: %s  FUNC: %s. ERR: %08X\r\n", pFuncDb[i].szDllName, pFuncDb[i].Func.pName, GetLastError() );
				}
			}
			else{//Force Load Here
			}
		}
		else if( pFuncDb[i].HookType == EXPORT_ORDINAL ){
			HMODULE hDLL = GetModuleHandle( pFuncDb[i].szDllName );
			if( hDLL != 0 ){
				pFuncDb[i].FuncAddr = (DWORD)GetProcAddress( hDLL, (LPCSTR)pFuncDb[i].Stuff );
				//str2log( "==> dll:%s ord: %d  func_addr: %08X\n",pFuncDb[i].szDllName,  pFuncDb[i].Stuff , pFuncDb[i].FuncAddr );

				if( pFuncDb[i].FuncAddr ){
					dwReady++;
				}
				else{//Error in GetProcAddress. Get error code
					str2log( "ExportByOrdinal failed. DLL: %s  ORD: %d. ERR: %08X\r\n", pFuncDb[i].szDllName, pFuncDb[i].Stuff, GetLastError() );
				}
			}
			else{//Force Load Here

			}
		}
		else if( pFuncDb[i].HookType == RVA_ADDR ){
			HMODULE hDLL = GetModuleHandle( pFuncDb[i].szDllName );
			if( hDLL != 0 ){
				pFuncDb[i].FuncAddr = (DWORD)hDLL + pFuncDb[i].Stuff;
				dwReady++;
			}
			else{//Force Load Here

			}
		}
	}

	if( !settings.ForceDllLoad ){//Set hook to ntdll.LdrLoadDll
		for( DWORD i = 0; i < dwHooks; i++ ){
			if(pFuncDb[i].HookType != ABSOLUTE_ADDR && pFuncDb[i].FuncAddr == 0){
				HMODULE hntdll = GetModuleHandle( "ntdll.dll" );
				DWORD origaddr = (DWORD)GetProcAddress(hntdll, "LdrLoadDll" );
				if(origaddr == 0)
					FatalError("GetProcAddress( ntdll.LdrLoadDll ) == NULL");
				GETADDR2( hntdll, LdrLoadDll )
				int err;
				//Hook LdrLoadDll
				new ((LPCVOID)origaddr, (LPCVOID)StubLdrLoadDll, &err, 0xffffffff ) KHOOK;

				break;
			}
		}
	}

	return dwReady;
}



inline char ToUp(char x){
	if(x >= 0x61 && x <= 0x7a)
		return x - 0x20;
	else
		return x;
}


//Not case sensive substr search
char* StrBufN(char *buf, char *str, int buflen){
	char Pattern[64];

	if(!buf || !str || !buflen) return 0;

	strncpy(Pattern, str, 64);
	Pattern[59] = '\0';

	int strlength = strlen(Pattern);
	if(strlength > buflen) return 0;//buffer smaller than substr

	//Make search pattern in up case
	for(DWORD i = 0; i < strlength; i++)
		Pattern[i] = ToUp(str[i]);


	if(strlength == buflen){//Equal strings length
		DWORD match = 0;
		for(DWORD k = 0; k < strlength; k++){
			if(Pattern[k] == ToUp(buf[k])) match++;
			else break;
		}
		if(match == strlength) return (char*)buf;
	}
	else{
		for(DWORD base = 0; base < (1 + buflen - strlength); base++){
			DWORD match = 0;
			for(int k = 0; k < strlength; k++){
				if(Pattern[k] == ToUp(buf[base + k])) match++;
				else break;
			}
			if(match == strlength) return (char*)&buf[base];
		}
	}
	return 0;
}


void Hooker(DWORD i){
	int err;
	char* szPrevName = IsAlreadyHooked((DWORD)hookdb[i].FuncAddr);
	if(szPrevName){
		str2log("ERROR: Function %s already hooked. Hooker function: %s\r\n", hookdb[i].Func.pName, szPrevName);
	}
	else if( hookdb[i].FuncAddr ){//If function address found

		if(settings.dwMode == MODE_SAFE){
			hookdb[i].pHook = new ((LPCVOID)hookdb[i].FuncAddr, (LPCVOID)ProxyPrologSafe, &err, i) KHOOK;
		}
		else{
			hookdb[i].pHook = new ((LPCVOID)hookdb[i].FuncAddr, (LPCVOID)ProxyProlog, &err, i) KHOOK;
		}

		if(!hookdb[i].pHook){
			str2log("ERROR: Can't set hook to %s : %s\r\n", hookdb[i].Func.pName, GetHookErrorText(err));
		}
	}
}

char* Type2Str(DWORD x){
	if(x==EXPORT_NAME)return "ExportByName";
	if(x==EXPORT_ORDINAL)return "ExportByOrdinal";
	if(x==RVA_ADDR) return "RVA";
	if(x==ABSOLUTE_ADDR) return "AbsoluteAddress";
	return "Unknown type";
}

void DumpDb(){
	str2log("-----------------------------\r\nDB Functions Dump\r\n");
	for(DWORD i = 0; i < dwHooks; i++){
		if( hookdb[i].HookType ==ABSOLUTE_ADDR){
			str2log( "Function: %s   Type:%s Addr:%08X\r\n", hookdb[i].Func.pName, Type2Str(hookdb[i].HookType), hookdb[i].FuncAddr );
		}else{
			str2log( "DLL: %s   Function: %s   Type:%s Addr:%08X\r\n", hookdb[i].szDllName, hookdb[i].Func.pName, Type2Str(hookdb[i].HookType), hookdb[i].FuncAddr );
		}
	}
	str2log("-----------------------------\r\n\r\n");
}



void GetAddr( HMODULE hmod, char* szName, void* pDst, DWORD Flag ){
	void* safe_addr = (void*)GetProcAddress( hmod, szName );
	if( !safe_addr ) FatalError( szName );

	if( Flag ){
		safe_addr =(void*)GetSafeFuncStartOrig( safe_addr );
		if( !safe_addr ) FatalError( szName );
	}

	DWORD dst = (DWORD)pDst;
	__asm{
		push edx
		push eax
		mov eax, safe_addr
		mov edx, dst
		mov [edx], eax
		pop eax
		pop edx
	}
}

void InitSafeFuncAddresses( HMODULE hKernel32, DWORD Flag ){
	KFUNC Funcs[]={
		{ "GetLastError", &safe_GetLastError },							//0
		{ "SetLastError", &safe_SetLastError },							//1
		{ "GetCurrentThreadId", &safe_GetCurrentThreadId },				//2
		{ "EnterCriticalSection", &safe_EnterCriticalSection },			//3
		{ "LeaveCriticalSection", &safe_LeaveCriticalSection },			//4
		{ "GetProcessHeap", &safe_GetProcessHeap },						//5
		{ "HeapAlloc", &safe_HeapAlloc },								//6
		{ "HeapFree", &safe_HeapFree },									//7
		{ "VirtualProtectEx", &safe_VirtualProtectEx },					//8
		{ "CloseHandle", &safe_CloseHandle },							//9
		{ "WriteFile", &safe_WriteFile },								//10
		{ "FlushFileBuffers", &safe_FlushFileBuffers },					//11
		{ "VirtualAlloc", &safe_VirtualAlloc },							//12
		{ "VirtualFree", &safe_VirtualFree },							//13
		{ "GetModuleFileNameW", &safe_GetModuleFileNameW },				//14
		{ "ExitProcess", &safe_ExitProcess },							//15
		{ "TlsAlloc", &safe_TlsAlloc },									//16
		{ "TlsFree", &safe_TlsFree },									//17
		{ "TlsSetValue", &safe_TlsSetValue },							//18
		{ "TlsGetValue", &safe_TlsGetValue },							//19
		{ "QueryPerformanceCounter", &safe_QueryPerformanceCounter },	//20
	};

	for( DWORD i = 0; i < 21; i++ ){
		KFUNC func = Funcs[i];
		GetAddr( hKernel32, func.szFunc, func.pAddr, Flag );

		if( func.pAddr == 0 ){
			FatalError( func.szFunc );
		}
	}
}
