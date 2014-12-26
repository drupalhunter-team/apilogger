//////////////////////////////////////////////////////////////////////////
// API Logger
// 1.0 ~12.2008     Initial version
// 1.1 (02.06.2009)
// 1.2 (07.08.2009) [30.08.2009 LegacyMode added]
// 1.3 (15.01.2010) GUI, Loader, DEP
// 1.4 (21.06.2010) DLL List print
// 1.5 (03.12.2010) Deffered DLL Load
// 1.6 (03.02.2011) Time line
//     (02.03.2011) Extended name bug fix (new Plugin SDK version)
// 1.7 (13.05.2011) Fake viri alert fix, 
//                  Absolute address extended name fix
//                  'About' from kerberos (modified)
// 1.7.1 (14.06.2011) Bug in GetFuncInfoById ( "Data dumper plugin" dev found)
// 1.8  (18.08.2011) Win7_64, Icon added, Error handling
// 1.9  10.01.2012  @ADDR fix, Function len 0xCC 0xCC fix
//      28.03.2012  Output value str output
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Windows.h>

#include "apilog.h"
#include "khook.h"
#include "klog.h"
#include "init.h"
#include "logger.h"
#include "dbparser.h"

#pragma comment(linker,"/MERGE:.rdata=.text")
#pragma comment(linker,"/ENTRY:DllMain")
#pragma comment(lib, "fpulib.lib")

//Global vars
KLOG *pLog;

SSETTINGS settings;

PFN_GetLastError				safe_GetLastError;
PFN_SetLastError				safe_SetLastError;
PFN_GetCurrentThreadId			safe_GetCurrentThreadId;
PFN_EnterCriticalSection		safe_EnterCriticalSection;
PFN_LeaveCriticalSection		safe_LeaveCriticalSection;
PFN_GetProcessHeap				safe_GetProcessHeap;
PFN_HeapAlloc					safe_HeapAlloc;
PFN_HeapFree					safe_HeapFree;
PFN_VirtualProtectEx			safe_VirtualProtectEx;
PFN_CloseHandle					safe_CloseHandle;
PFN_WriteFile					safe_WriteFile;
PFN_FlushFileBuffers			safe_FlushFileBuffers;
PFN_VirtualAlloc				safe_VirtualAlloc;
PFN_VirtualFree					safe_VirtualFree;
PFN_wvsprintfA					safe_wvsprintfA;
PFN_GetModuleFileNameW			safe_GetModuleFileNameW;
PFN_ExitProcess					safe_ExitProcess;
PFN_TlsAlloc					safe_TlsAlloc;
PFN_TlsFree						safe_TlsFree;
PFN_TlsSetValue					safe_TlsSetValue;
PFN_TlsGetValue					safe_TlsGetValue;
PFN_LdrLoadDll					safe_LdrLoadDll;
PFN_QueryPerformanceCounter     safe_QueryPerformanceCounter;

DWORD		hIntruder = 0;
SFUNCDB*	hookdb = 0;
DWORD		dwHooks = 0;
DWORD		dwPluginHooks = 0;
CRITICAL_SECTION csLog;
CRITICAL_SECTION cs;
DWORD		ExeImageBase = 0;
DWORD		ExeSizeOfImage = 0;
DWORD		dwTlsIndex = 0; 
DWORD		dwExcludeModules = 0;
char**		ppExcludeModules = 0;
DWORD		dwIncludeModules = 0;
char**		ppIncludeModules = 0;
DWORD		StartUpDone = 0;

STHREAD*	sthreads = 0;
DWORD		adrExitThread = 0;

LARGE_INTEGER TimerFreq;
LARGE_INTEGER TimerStart;
SYSTEMTIME    StartTime;

HMODULE g_hKernel32 = 0;


LPVOID MyTlsGetValue(DWORD dwTlsIndex){
	LPVOID lpvData; 

	// Retrieve a data pointer for the current thread.
	lpvData = safe_TlsGetValue(dwTlsIndex); 

	// If NULL, allocate memory for this thread.
	if (lpvData == NULL){ 
		lpvData = (LPVOID) MemAlloc(sizeof(STHREAD));
		if (lpvData != NULL) 
			safe_TlsSetValue(dwTlsIndex, lpvData); 
	}
	return lpvData;
}

void AllocStruct(){
	LPVOID lpvData; 
	lpvData = MemAlloc(sizeof(STHREAD));
	if(lpvData) safe_TlsSetValue(dwTlsIndex, lpvData);
}

void FreeStruct(){
	LPVOID lpvData; 
	lpvData = safe_TlsGetValue(dwTlsIndex); 
	if (lpvData) MemFree(lpvData); 
}

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved){
	switch (ul_reason_for_call){
		case DLL_PROCESS_ATTACH:
			InitLogger((DWORD)hModule);
			break;
		case DLL_PROCESS_DETACH:
			DeInitLogger();
			FreeStruct();
			safe_TlsFree(dwTlsIndex);
			break;
		case DLL_THREAD_ATTACH:
			AllocStruct();
			break;
		case DLL_THREAD_DETACH:
			FreeStruct();
			break;
	}
	return TRUE;
}


__declspec(noreturn) void FatalError(char *msg){
	MessageBox(0, msg, "intruder.dll", MB_ICONERROR|MB_TOPMOST);
	ExitProcess(-1);
}


void ReadSettings(DWORD hMod){
	char szBuf[MAX_PATH];
	char szBuf2[2048];
	char szBuf3[MAX_PATH];

	GetModuleFileName((HMODULE)hMod, szBuf, MAX_PATH);
	for(DWORD i=(DWORD)strlen(szBuf); i>0; i--){if(szBuf[i-1]=='\\'){szBuf[i]=0; break;}}
	strcat(szBuf, "settings.ini");

	settings.PELoader	= GetPrivateProfileInt("Settings", "PELoader", 0, szBuf);
	settings.DisableKernel32Load	= GetPrivateProfileInt("Settings", "DisableKernel32Load", 0, szBuf);
	settings.ForceDllLoad	= GetPrivateProfileInt("Settings", "ForceDllLoad", 0, szBuf);
	settings.DumpDb= GetPrivateProfileInt("Settings", "DumpDb", 0, szBuf);
	settings.strminlen	= GetPrivateProfileInt("Settings", "MinStrLen", 4, szBuf);
	settings.strmaxlen	= GetPrivateProfileInt("Settings", "MaxStrLen", 100, szBuf);
	settings.fOnlyFirst	= GetPrivateProfileInt("Settings", "RootFunc", 0, szBuf);
	settings.fLogTID	= GetPrivateProfileInt("Settings", "TID", 1, szBuf);
	settings.dwPluginHooks=GetPrivateProfileInt("Settings", "PluginHooks", 0, szBuf);
	settings.fExtFuncNames=GetPrivateProfileInt("Settings", "ExtFuncNames", 0, szBuf);
	settings.fLogOnlyExeCalls=GetPrivateProfileInt("Settings", "OnlyExeCalls", 0, szBuf);
	settings.fDisableLog= GetPrivateProfileInt("Settings", "DisableLog", 0, szBuf);
	settings.dwMode= GetPrivateProfileInt("Settings", "Mode", 0, szBuf);
	settings.Profiler= GetPrivateProfileInt("Settings", "Profiler", 0, szBuf);
	settings.Time= GetPrivateProfileInt("Settings", "Time", 0, szBuf);

	if(settings.strminlen > settings.strmaxlen){
		settings.strmaxlen = settings.strminlen + 1;
	}

	//OutputFile
	GetPrivateProfileString("Settings", "OutLogFile", "", szBuf2, 260, szBuf);
	if(szBuf2[0]!=0){//Output file defined in settings.ini
		if(szBuf2[1]==':'){//Full path
			strcpy(settings.szOutFile, szBuf2);
		}
		else{//Create full path from target exe dir
			GetModuleFileName((HMODULE)0, szBuf3, MAX_PATH);
			for(DWORD i=(DWORD)strlen(szBuf3); i>0; i--){if(szBuf3[i-1]=='\\'){szBuf3[i]=0; break;}}
			strcat(szBuf3, szBuf2);
			strcpy(settings.szOutFile, szBuf3);
		}
	}
	else{//Create full path for log File
		GetModuleFileName(0, szBuf3, MAX_PATH);
		size_t len=strlen(szBuf3);
		if(szBuf3[len-4]=='.') szBuf3[len-4]='\0';
		strcat(szBuf3, ".apilog.txt");
		strcpy(settings.szOutFile, szBuf3);
	}


	//Load exclude modules list
	GetPrivateProfileString("Settings", "ExcludeModules", "", szBuf2, 2048, szBuf);
	ppExcludeModules = CrackString(szBuf2, (int*)&dwExcludeModules);
	if(dwExcludeModules){
		for(int i=0; i<dwExcludeModules; i++){
			ToUpper(ppExcludeModules[i]);
		}
	}

	//Load include modules list
	GetPrivateProfileString("Settings", "IncludeModules", "", szBuf2, 2048, szBuf);
	ppIncludeModules = CrackString(szBuf2, (int*)&dwIncludeModules);
	if(dwIncludeModules){
		for(int i=0; i<dwIncludeModules; i++){
			ToUpper(ppIncludeModules[i]);
		}
	}

	//Database file
	GetPrivateProfileString("Settings", "DBFile", "db.txt", szBuf2, 260, szBuf);
	if(szBuf2[1]==':'){
		strcpy(settings.szDBFile, szBuf2);
	}
	else{
		GetModuleFileName((HMODULE)hMod, szBuf, MAX_PATH);
		for(DWORD i=(DWORD)strlen(szBuf); i>0; i--){if(szBuf[i-1]=='\\'){szBuf[i]=0; break;}}
		strcat(szBuf, szBuf2);
		strcpy(settings.szDBFile, szBuf);
	}
}

void *MemAllocTrue(DWORD size){
	return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void MemFreeTrue(void *p){
	if(!p) return;
	HeapFree(GetProcessHeap(), 0, p);
}


void *MemAlloc(DWORD size){
	return safe_HeapAlloc(safe_GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void MemFree(void *p){
	if(!p) return;
	safe_HeapFree(safe_GetProcessHeap(), 0, p);
}

DWORD IsAddrInModule(DWORD Addr, char** pp, DWORD cnt){
	char buf[32];

	GetModuleNameByAddress(Addr, buf);
	ToUpper(buf);
	for(DWORD i=0; i<cnt; i++){
		if(strstr(buf, pp[i])) return 1;
	}
	return 0;
}

DWORD CanLog(DWORD Addr){
	if(!settings.fLogOnlyExeCalls && !dwExcludeModules && !dwIncludeModules) return 1;
	
	//fLogOnlyExe && ExeImageBase <= Addr < ExeImageBase+ExeSizeOfImage
	if((Addr >= ExeImageBase) && (Addr < (ExeImageBase + ExeSizeOfImage))) return 1;
	
	//ExcludeModules are defined
	if(!settings.fLogOnlyExeCalls && dwExcludeModules && !IsAddrInModule(Addr, ppExcludeModules, dwExcludeModules)) return 1;

	if(!settings.fLogOnlyExeCalls && dwIncludeModules && IsAddrInModule(Addr, ppIncludeModules, dwIncludeModules)) return 1;

	return 0;
}

DWORD IsStartUp(DWORD Addr){
	if(StartUpDone==1) return 0;

	if(StartUpDone==0 && ((Addr >= ExeImageBase) && (Addr < (ExeImageBase + ExeSizeOfImage)))){
		StartUpDone=1;
		return 0;
	}
	else if(StartUpDone==0){
		return 1;
	}
	return 0;
}

DWORD IsExitThreadFunc(DWORD id){
	if(hookdb[id].FuncAddr == adrExitThread) return 1;
	return 0;
}

void __stdcall ProxyEntry(SPROXYENTRYSTRUCT *pInfo, DWORD dwEnterTacts){	
	DWORD id = pInfo->funcid;
	DWORD FakeFuncAddr=-1;

//	__asm{
//		__emit 0xeb
//		__emit 0xfe
//	}
	if(CanLog(pInfo->retaddr) && !IsStartUp(pInfo->retaddr) && !IsExitThreadFunc(id)){
		KROUTINE* Routine = Push();
		if(Routine){
//			str2log("ProxyEntry TID=%08X. FuncID=%08X. %s RETADDR: %08X %08X %08X\r\n", safe_GetCurrentThreadId(), id, hookdb[id].Func.pName, pInfo->retaddr, ExeImageBase, ExeImageBase + ExeSizeOfImage);

			Routine->EnterTimeQC.QuadPart = 0;
			safe_QueryPerformanceCounter( &Routine->EnterTimeQC );

			memset(Routine, 0, sizeof(Routine));
			Routine->EnterTime = dwEnterTacts;
			Routine->FuncId = id;
			Routine->RetAddr = pInfo->retaddr;
			Routine->pStack = &pInfo->parameters[0];
			Routine->Func = hookdb[id].Func;
		
			//Plugin routine call
			if(Routine->Func.BeforeFunc){
				FakeFuncAddr = Routine->Func.BeforeFunc(pInfo);
			}

			//Save function in stuf
			Routine->InRegs.eax = pInfo->eax;
			Routine->InRegs.ebp = pInfo->ebp;
			Routine->InRegs.ebx = pInfo->ebx;
			Routine->InRegs.ecx = pInfo->ecx;
			Routine->InRegs.edi = pInfo->edi;
			Routine->InRegs.edx = pInfo->edx;
			Routine->InRegs.eflags = pInfo->eflags;
			Routine->InRegs.esi = pInfo->esi;
			Routine->InRegs.esp = pInfo->esp;

			SEXTENDEDREGS ExRegs;
			__asm{fxsave ExRegs}
			Routine->InExRegs = ExRegs;

			//Get module name
			GetModuleNameByAddress(pInfo->retaddr, Routine->szModule);
			CollectData2(Routine);

			pInfo->retaddr = (DWORD)ProxyEpilog;
		}
		else{
			str2log("ProxyEntry.Push failed.\r\n");
		}
	}

	if(FakeFuncAddr == 0 || FakeFuncAddr == -1){
		pInfo->funcid = (DWORD)hookdb[id].pHook->exec_buf;
	}
	else{
		pInfo->funcid = FakeFuncAddr;//Change function address
	}
}


DWORD OverHead=0;

__declspec(naked) void ProxyProlog(void){
	__asm{
		pushfd
		pushad

		rdtsc
		shrd	eax, edx, 8
		push	eax
		sub		eax, OverHead
		push	eax
		lea		eax, [esp + 8]
		push	eax
		call	ProxyEntry
		pop		ecx
		rdtsc
		shrd	eax, edx, 8
		sub		eax, ecx
		add		OverHead, eax

		popad
		popfd
		retn
	}
}

void __stdcall ProxyExit(SPROXYEXIT* pExitInfo, DWORD dwLeaveTacts){
	KROUTINE* Routine = LookupStack();
	if(Routine){
//		str2log("ProxyExit. TID=%08X. FuncID=%08X, %s\r\n", safe_GetCurrentThreadId(), Routine->FuncId, hookdb[Routine->FuncId].Func.pName);
		Routine->LeaveTimeQC.QuadPart = 0;
		safe_QueryPerformanceCounter( &Routine->LeaveTimeQC );

		//Save function info
		Routine->LeaveTime=dwLeaveTacts;
		Routine->RetVal=pExitInfo->result;

		if(Routine->Func.AfterFunc){
			DWORD NewRetVal = Routine->Func.AfterFunc(pExitInfo, pExitInfo->result);
			Routine->RetVal = NewRetVal;// New value for logger

			DWORD pRealRetVal = (DWORD)pExitInfo - 8;
			*(DWORD*)pRealRetVal = NewRetVal;
		}


		//Added in v1.9 -> Try to decode out value as string
		Routine->OutVal.param = Routine->RetVal;
		Routine->OutVal.str   = GetStrByAddress( ( BYTE* )Routine->RetVal, settings.strminlen, settings.strmaxlen );


		pExitInfo->result = Routine->RetAddr;
		Pop();
		Dump();
	}
	else{
		str2log("ERROR: ProxyExit.LookupStack failed\r\n");
		safe_ExitProcess(0);
	}
}

__declspec(naked) void ProxyEpilog(void){
	__asm{
		push	eax
		pushfd
		pushad

		rdtsc
		shrd	eax, edx, 8
		push	eax
		sub		eax, OverHead
		push	eax
		lea		eax, [esp + 4*11]
		push	eax
		call	ProxyExit
		pop		ecx
		rdtsc
		shrd	eax, edx, 8
		sub		eax, ecx
		add		OverHead, eax

		popad
		popfd
		retn
	}
}

KROUTINE* Push(){
	KROUTINE* res = 0;
	STHREAD*  sth = 0;
	
	if(settings.dwMode == MODE_LEGACY){
		sth = LookUpThread(safe_GetCurrentThreadId());
		if(!sth){
			str2log("ERROR: Push.LookUpThread failed\r\n");
			safe_ExitProcess(0);
		}

		res = (KROUTINE*)MemAlloc(sizeof(KROUTINE));
		sth->pStack[sth->cur_tos] = res;


		if(sth->cur_tos >= MAX_DEPTH){
			str2log("ERROR: Push failed. Stack pointer > MAX_DEPTH\r\n");
			safe_ExitProcess(0);
		}

		if(sth->cur_tos > sth->max_tos) sth->max_tos = sth->cur_tos;
	}
	else{
		sth = (STHREAD*)MyTlsGetValue(dwTlsIndex); 
		if(sth==0){
			str2log("Push.TlsGetValue == 0\r\n");
			safe_ExitProcess(0);
		}

		sth->tid = safe_GetCurrentThreadId();

		//Mem alloc for new KROUTINE struct
		res = (KROUTINE*)MemAlloc(sizeof(KROUTINE));
		sth->pStack[sth->cur_tos] = res;
	}


	sth->pStack[sth->cur_tos]->ent   = sth->cur_tos;
	sth->pStack[sth->cur_tos]->index = sth->last_index;

	sth->cur_tos++;
	sth->last_index++;

	if(sth->cur_tos >= MAX_DEPTH){
		str2log("ERROR: Push failed. Stack pointer > MAX_DEPTH\r\n");
		safe_ExitProcess(0);
	}

	if(sth->cur_tos > sth->max_tos) sth->max_tos = sth->cur_tos;

	return res;
}

KROUTINE* LookupStack(){
	STHREAD* sth=0;
	if(settings.dwMode == MODE_LEGACY){
		sth = LookUpThread(safe_GetCurrentThreadId());
		if(!sth){
			str2log("ERROR: Push.LookUpThread failed\r\n");
			safe_ExitProcess(0);
		}
	}
	else{
		sth = (STHREAD*)safe_TlsGetValue(dwTlsIndex);
		if(sth == 0){
			str2log("LookupStack.TlsGetValue == 0\r\n");
			safe_ExitProcess(0);
		}
	}

	if(sth->cur_tos){
		return sth->pStack[sth->cur_tos - 1];
	}
	else{
		str2log("ERROR: LookupStack Failed. Zero stack pointer\r\n");
		safe_ExitProcess(0);
	}
	return 0;
}

void Pop(){
	STHREAD* sth = 0;
	if(settings.dwMode == MODE_LEGACY){
		sth = LookUpThread(safe_GetCurrentThreadId());
		if(!sth){
			str2log("ERROR: Push.LookUpThread failed\r\n");
			safe_ExitProcess(0);
		}
	}
	else{
		sth = (STHREAD*)safe_TlsGetValue(dwTlsIndex);
		if(sth==0){
			str2log("Pop.TlsGetValue == 0\r\n");
			safe_ExitProcess(0);
		}
	}

	sth->cur_tos--;
	if(sth->cur_tos < 0){
		str2log("ERROR: Pop failed. Negative stack pointer\r\n");
		safe_ExitProcess(0);
	}

	//Save KROUTINE* from stack array to store
	if(sth->store_idx < MAX_DEPTH){
		sth->pStore[sth->store_idx] = sth->pStack[sth->cur_tos];	
		sth->store_idx++;
	}
	else{
		//Max. store depth!
		sth->MaxDepth = 1;
	}
}

__declspec(naked) void ProxyPrologSafe(void){
	__asm{
		pushfd
		pushad

		rdtsc
		shrd	eax, edx, 8
		push	eax
		sub		eax, OverHead
		push	eax
		lea		eax, [esp + 8]
		push	eax
		call	ProxyEntrySafe
		pop		ecx
		rdtsc
		shrd	eax, edx, 8
		sub		eax, ecx
		add		OverHead, eax

		popad
		popfd
		retn
	}
}

void __stdcall ProxyEntrySafe(SPROXYENTRYSTRUCT *pInfo, DWORD dwEnterTacts){	
	KROUTINE* Routine = 0;
	DWORD id = pInfo->funcid;
	DWORD FakeFuncAddr=-1;
	
	if(CanLog(pInfo->retaddr)){
		Routine = (KROUTINE*)MemAlloc(sizeof(KROUTINE));
		if(Routine){
			Routine->EnterTime = dwEnterTacts;
			Routine->FuncId = id;
			Routine->RetAddr = pInfo->retaddr;
			Routine->pStack = &pInfo->parameters[0];
			Routine->Func = hookdb[id].Func;

			//Plugin routine call
			if(Routine->Func.BeforeFunc){
				FakeFuncAddr = Routine->Func.BeforeFunc(pInfo);
			}

			//Save function in stuf
			Routine->InRegs.eax = pInfo->eax;
			Routine->InRegs.ebp = pInfo->ebp;
			Routine->InRegs.ebx = pInfo->ebx;
			Routine->InRegs.ecx = pInfo->ecx;
			Routine->InRegs.edi = pInfo->edi;
			Routine->InRegs.edx = pInfo->edx;
			Routine->InRegs.eflags = pInfo->eflags;
			Routine->InRegs.esi = pInfo->esi;
			Routine->InRegs.esp = pInfo->esp;

			SEXTENDEDREGS ExRegs;
			__asm{fxsave ExRegs}
			Routine->InExRegs = ExRegs;

			//Get module name
			GetModuleNameByAddress(pInfo->retaddr, Routine->szModule);
			CollectData2(Routine);

			safe_EnterCriticalSection(&csLog);
			//Log
			Out2Log2(safe_GetCurrentThreadId(), Routine);
			safe_LeaveCriticalSection(&csLog);
		
			CleanMemory2(Routine);
		}
		else{
			str2log("ERROR: ProxyEntry.MemAlloc(sizeof(KROUTINE)) failed\r\n");
			safe_ExitProcess(0);
		}
	}

	if(FakeFuncAddr == 0 || FakeFuncAddr == -1){
		pInfo->funcid = (DWORD)hookdb[id].pHook->exec_buf;	////Change function address to function
	}
	else{
		pInfo->funcid = FakeFuncAddr;//Change function address from plugin value
	}

	MemFree(Routine);
	
}

void Dump(){
	STHREAD* th_data = 0;
	if(settings.dwMode == MODE_LEGACY){
		th_data = LookUpThread(safe_GetCurrentThreadId());
		if(!th_data){
			str2log("ERROR: Push.LookUpThread failed\r\n");
			safe_ExitProcess(0);
		}
	}
	else{
		th_data = (STHREAD*)safe_TlsGetValue(dwTlsIndex);
		if(th_data == 0){
			str2log("Dump.TlsGetValue == 0\r\n");
			safe_ExitProcess(0);
		}
	}
	if(th_data->cur_tos==0){
		safe_EnterCriticalSection(&csLog);
		
		for(DWORD i=0; i < th_data->store_idx; i++){
			for(DWORD j=0; j < th_data->store_idx; j++){
				if(th_data->pStore[j]->index == i){
					if(settings.fOnlyFirst){
						if(i==0){
							Out2Log2(th_data->tid, th_data->pStore[j]);
						}
					}
					else{
						Out2Log2(th_data->tid, th_data->pStore[j]);
					}
					break;
				}
			}
		}

		if(th_data->MaxDepth && !settings.fOnlyFirst){
			pLog->Write("......\r\n");
		}
		safe_LeaveCriticalSection(&csLog);

		//Free memory
		for(DWORD i=0; i < th_data->store_idx; i++){
			CleanMemory2(th_data->pStore[i]);
			MemFree(th_data->pStore[i]);
		}

		th_data->tid=0;
		th_data->store_idx=0;
		th_data->max_tos=0;
		th_data->cur_tos=0;
		th_data->last_index=0;
		th_data->MaxDepth=0;
	}
}

STHREAD* LookUpThread(DWORD tid){
	STHREAD* res=0;
	DWORD	fFound=0;

	for(DWORD i=0; i < MAX_THREADS; i++){
		if(sthreads[i].tid == tid){
			res = &sthreads[i];
			fFound = 1;
			break;
		}
	}
	if(!fFound){
		safe_EnterCriticalSection(&cs);

		for(DWORD i = 0; i < MAX_THREADS; i++){
			if(sthreads[i].tid == 0){
				sthreads[i].tid = tid;
				res = &sthreads[i];
				break;
			}
		}
		safe_LeaveCriticalSection(&cs);
	}
	return res;//No empty cells
}
