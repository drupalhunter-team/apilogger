
#include "stdafx.h"
#include <Windows.h>

#include "apilog.h"
#include "khook.h"
#include "klog.h"
#include "init.h"
#include "logger.h"
#include "commondat.h"

extern HMODULE g_hKernel32;

void CollectData2(KROUTINE* p){

	if(p->Func.params){//Malloc for strucs array
		p->pInParams=(SPARAM*)MemAlloc(p->Func.params * sizeof(SPARAM));
	}
	else{
		p->pInParams=0;
	}

	SPARAM* p1 = p->pInParams;
	DWORD* pstack = p->pStack;

	if(p1){
		for(DWORD i=0; i<p->Func.params; i++){
			p1->param = pstack[i];
			p1->str = GetStrByAddress((BYTE*)pstack[i], settings.strminlen, settings.strmaxlen);
			p1++;
		}
	}

	//save reg str
	p->InRegStr.str_eax=GetStrByAddress((BYTE*)p->InRegs.eax, settings.strminlen, settings.strmaxlen);
	p->InRegStr.str_ebp=GetStrByAddress((BYTE*)p->InRegs.ebp, settings.strminlen, settings.strmaxlen);
	p->InRegStr.str_ebx=GetStrByAddress((BYTE*)p->InRegs.ebx, settings.strminlen, settings.strmaxlen);
	p->InRegStr.str_ecx=GetStrByAddress((BYTE*)p->InRegs.ecx, settings.strminlen, settings.strmaxlen);
	p->InRegStr.str_edi=GetStrByAddress((BYTE*)p->InRegs.edi, settings.strminlen, settings.strmaxlen);
	p->InRegStr.str_edx=GetStrByAddress((BYTE*)p->InRegs.edx, settings.strminlen, settings.strmaxlen);
	p->InRegStr.str_esi=GetStrByAddress((BYTE*)p->InRegs.esi, settings.strminlen, settings.strmaxlen);
}


void CleanMemory2(KROUTINE* p){

	SPARAM *p1=p->pInParams;

	if(p1){
		for(DWORD i=0; i < p->Func.params; i++){
			MemFree(p1->str);
			p1++;
		}
	}

	MemFree(p->pInParams);

	MemFree(p->InRegStr.str_eax);
	MemFree(p->InRegStr.str_ebp);
	MemFree(p->InRegStr.str_ebx);
	MemFree(p->InRegStr.str_ecx);
	MemFree(p->InRegStr.str_edi);
	MemFree(p->InRegStr.str_edx);
	MemFree(p->InRegStr.str_esi);
	
	//v1.9
	MemFree( p->OutVal.str );
}


DWORD GetLenA(BYTE *p, DWORD maxlen){
	DWORD len=0;

	for(DWORD i=0; i<maxlen; i++){
		if(p[i]>=0x20 && p[i]<=0x7F) len++;
		else break;
	}
	return len;
}


DWORD GetLenW(WORD *p, DWORD maxlen){
	DWORD len=0;
	for(DWORD i=0; i<maxlen; i++){
		if(p[i]>=0x20 && p[i]<=0x7F) len++;
		else break;
	}
	return len;
}


EXCEPTION_DISPOSITION __cdecl _except_handler(
		struct _EXCEPTION_RECORD *ExceptionRecord,
		void * EstablisherFrame,
		struct _CONTEXT *ContextRecord,
		void * DispatcherContext)
{
	ContextRecord->Eip = ContextRecord->Eip+6;
	ContextRecord->Ebx=0;
	return ExceptionContinueExecution;
}

DWORD IsGoodForRead(BYTE *p, DWORD maxlen){
	DWORD handler = (DWORD)_except_handler;
	DWORD retv=0;

	__asm{
		push	handler
		push	fs:[0]
		mov		fs:[0], esp

		mov		ecx, maxlen
		mov		ebx, 1
		mov		edx, p
loop1:
		mov		al, [edx]
		inc		edx
		dec		ecx
		jnz		loop1
	
		mov		eax,[esp]
		mov		fs:[0], eax
		add		esp, 8

		mov		retv, ebx
	}
	return retv;
}



void Unicode2Ascii(WORD *s, BYTE *d, DWORD len){
	for(DWORD i=0; i<len; i++){
		d[i]=(BYTE)(s[i] & 0xFF);
	}
}

char* GetStrByAddress(BYTE *p, DWORD minlen, DWORD maxlen){
	char *pRet=0;
	DWORD len=0, len1=0;

	//range check
	if((DWORD)p<0x10000 || (DWORD)p>0x7FFFFFFF) return 0;

	//check ascii
	if(!IsGoodForRead(p, maxlen+1)) return 0;

	len=GetLenA(p, maxlen+1);//check for strlen>max allowed len
	if(len >= minlen){	//ascii
		len1=len;
		if(len==maxlen+1) len=maxlen;

		pRet=(char *)MemAlloc(len+4);//alloc for str, '.' '.' '.' '\0'
		if(pRet){
			memcpy(pRet, p, len);
			if(len1==maxlen+1) strcat(pRet, "...");
		}
	}
	else{			//unicode
		if(IsGoodForRead(p, 2*maxlen+2)){
			len=GetLenW((WORD*)p, maxlen+1);
			if(len>minlen){
				len1=len;
				if(len==maxlen+1) len=maxlen;
				pRet=(char *)MemAlloc(len+4);
				if(pRet){
					//copy unicode str
					Unicode2Ascii((WORD*)p, (BYTE*)pRet, len);
					if(len1==maxlen+1) strcat(pRet, "...");
				}
			}
		}
	}
	return pRet;
}

// 8syms dot 3ext=12syms+zero
void GetModuleNameByAddress(DWORD p, char *szName){
	char szBuffer[MAX_PATH]={0};
	WORD szBufUnic[MAX_PATH]={0};

	DWORD len=0, i=0;

	(DWORD)p &= 0xFFFF0000;

	while(p>0x10000){
		len=safe_GetModuleFileNameW((HMODULE)p, szBufUnic, MAX_PATH);
		if(len) break;

		p-=0x10000;
	}

	if(len){
		Unicode2Ascii(szBufUnic, (BYTE*)szBuffer, len);
		for(i=len-1; i>=0; i--){
			if(szBuffer[i]=='\\'){
				len=strlen(&szBuffer[i+1]);
				if(len<=12){//module name less
					strcpy(szName, &szBuffer[i+1]);
				}
				else{
					if(szBuffer[i+1+len-4]=='.'){//normal extension. write ~.ext at end of module name
						memcpy(szName, &szBuffer[i+1], 7);
						szName[7]=0;
						strcat(szName, "~");
						strcat(szName, &szBuffer[i+1+len-4]);
					}
					else{
						memcpy(szName, &szBuffer[i+1], 11);
						szName[11]=0;
						strcat(szName, "~");
					}
				}
				break;
			}
		}
	}
	else{
		strcpy(szName, "NOMODULE");
	}

	//add spaces after module name if needed
	len = strlen(szName);
	if(len<12){
		for(i=0; i<12-len; i++) strcat(szName, " ");
	}
}




void Timee( LARGE_INTEGER* pel, SYSTEMTIME* pOutTime, DWORD* pUs ){
	*pOutTime = StartTime;

	DWORD hourAdd = (DWORD)( pel->QuadPart / 3600000000 );
	if( hourAdd > 0 ){
		pel->QuadPart -= hourAdd * 3600000000;
	}

	DWORD minAdd  = pel->QuadPart / 60000000;
	if( minAdd > 0 ){
		pel->QuadPart -= minAdd * 60000000;
	}

	DWORD secAdd  = pel->QuadPart / 1000000;
	if( secAdd > 0 ){
		pel->QuadPart -= secAdd * 1000000;
	}

	DWORD milAdd  = pel->QuadPart / 1000;
	if( milAdd > 0 ){
		pel->QuadPart -= milAdd * 1000;
	}

	*pUs = pel->QuadPart;

	//Time prepare
	pOutTime->wMilliseconds += milAdd;//no need correct - inited as 0

	pOutTime->wSecond += secAdd;
	if( pOutTime->wSecond >= 60 ){
		pOutTime->wSecond -= 60;
		pOutTime->wMinute++;
		if( pOutTime->wMinute >= 60 ){
			pOutTime->wMinute -= 60;
			pOutTime->wHour++;
		}
	}

	pOutTime->wMinute += minAdd;
	if( pOutTime->wMinute >= 60 ){
		pOutTime->wMinute -= 60;
		pOutTime->wHour++;
	}

	pOutTime->wHour   += hourAdd;

}


void Out2Log2(DWORD tid, KROUTINE *p){
	//If #nolog option enabled
	if(p->Func.fNoLog) return;

	//Filter by EXE.
//	if(settings.fLogOnlyExeCalls && !strstr(p->szModule, szExeModule)) return;

	//Log time
	if(settings.Time){
		//Calculate time:  StartTime + (EnterTime-TimerStart)

		LARGE_INTEGER usDelta;
		usDelta.QuadPart = ( p->EnterTimeQC.QuadPart - TimerStart.QuadPart ) * 1000000 / TimerFreq.QuadPart;
		
		DWORD      out_us = 0;
		SYSTEMTIME out_time;
		Timee( &usDelta, &out_time, &out_us );
		//pLog->Write("%d  ", (DWORD)usDelta.QuadPart);
		pLog->Write("%02d:%02d:%02d:%03d:%03d  ", out_time.wHour, out_time.wMinute,out_time.wSecond, out_time.wMilliseconds, out_us );
	}


	pLog->Write("%s %08X", p->szModule, p->RetAddr);
	if(settings.fLogTID){
		pLog->Write(" %04X ", tid);
	}
	else{
		pLog->Write(" ");
	}
	//print spaces before func name
	if(p->ent!=0){
		for(DWORD j=0; j<p->ent; j++){
			pLog->Write(" ");
		}
	}

	//function name or extended function name
	if( !settings.fExtFuncNames ){
		pLog->Write("%s(", p->Func.pName);
	}
	else{
		if( p->Func.pExtName ){
			pLog->Write("%s(", p->Func.pExtName);
		}
		else{
			pLog->Write("%s(", p->Func.pName);
		}
	}

	if(p->Func.params > 0){
		SPARAM *pSParam=p->pInParams;
		if(pSParam){
			if(p->Func.params > 1){
				for(DWORD i=0; i < p->Func.params - 1; i++){
					pLog->Write("%08X", pSParam->param);
					if(pSParam->str) pLog->Write(": \"%s\", ", pSParam->str);			
					else{
						pLog->Write(", ");
					}
					pSParam++;
				}
			}
			pLog->Write("%08X", pSParam->param);
			if(pSParam->str) pLog->Write(": \"%s\"", pSParam->str);
		}
	}

	//Return value save in log
	if(settings.dwMode == MODE_SAFE){//Safe log
		pLog->Write(")\r\n");
	}
	else{
		pLog->Write(") ret: %08X", p->RetVal);

		if(p->Func.fDumpTacts && TimerFreq.QuadPart != 0){
			//pLog->Write(" [%d]\r\n", p->LeaveTime - p->EnterTime);
			DWORD us = (p->LeaveTimeQC.QuadPart - p->EnterTimeQC.QuadPart) * 1000000 / TimerFreq.QuadPart;
			DWORD tics = (p->LeaveTimeQC.QuadPart - p->EnterTimeQC.QuadPart);
			pLog->Write(" [%u] [%u]", /*p->LeaveTime - p->EnterTime, */ us, tics );
		}
		
		//Decoded string write (if exist)
		if( p->OutVal.str ) pLog->Write( " -> \"%s\"", p->OutVal.str );
		//pLog->Write( "OUTV %08X", p->OutVal.param );
		pLog->Write("\r\n");
	}



	//Additional function data
	if(p->Func.fDumpRegs){
		Reg2Log("EAX", p->InRegs.eax, p->InRegStr.str_eax);
		Reg2Log("ECX", p->InRegs.ecx, p->InRegStr.str_ecx);
		Reg2Log("EDX", p->InRegs.edx, p->InRegStr.str_edx);
		Reg2Log("EBX", p->InRegs.ebx, p->InRegStr.str_ebx);
		Reg2Log("EBP", p->InRegs.ebp, p->InRegStr.str_ebp);
		Reg2Log("ESI", p->InRegs.esi, p->InRegStr.str_esi);
		Reg2Log("EDI", p->InRegs.edi, p->InRegStr.str_edi);
		pLog->Write("\r\n");
	}

	//ECX
	if(!p->Func.fDumpRegs && p->Func.fEcx){
		Reg2Log("ECX", p->InRegs.ecx, p->InRegStr.str_ecx);
	}

	//ECX
	if(!p->Func.fDumpRegs && p->Func.fEax){
		Reg2Log("EAX", p->InRegs.eax, p->InRegStr.str_eax);
	}

	//FPU
	if(p->Func.fDumpFpu){
		Fpu2Log("ST0", (BYTE*)&p->InExRegs.st0);
		Fpu2Log("ST1", (BYTE*)&p->InExRegs.st1);
		Fpu2Log("ST2", (BYTE*)&p->InExRegs.st2);
		Fpu2Log("ST3", (BYTE*)&p->InExRegs.st3);
		Fpu2Log("ST4", (BYTE*)&p->InExRegs.st4);
		Fpu2Log("ST5", (BYTE*)&p->InExRegs.st5);
		Fpu2Log("ST6", (BYTE*)&p->InExRegs.st6);
		Fpu2Log("ST7", (BYTE*)&p->InExRegs.st7);
		pLog->Write("\r\n");
	}

	//MMX
	if(p->Func.fDumpMMX){
		Mmx2Log("MM0", (BYTE*)&p->InExRegs.st0);
		Mmx2Log("MM1", (BYTE*)&p->InExRegs.st1);
		Mmx2Log("MM2", (BYTE*)&p->InExRegs.st2);
		Mmx2Log("MM3", (BYTE*)&p->InExRegs.st3);
		Mmx2Log("MM4", (BYTE*)&p->InExRegs.st4);
		Mmx2Log("MM5", (BYTE*)&p->InExRegs.st5);
		Mmx2Log("MM6", (BYTE*)&p->InExRegs.st6);
		Mmx2Log("MM7", (BYTE*)&p->InExRegs.st7);
		pLog->Write("\r\n");
	}

	//XMM
	if(p->Func.fDumpXMM){
		Xmm2Log("XMM0", (BYTE*)&p->InExRegs.xmm0);
		Xmm2Log("XMM1", (BYTE*)&p->InExRegs.xmm1);
		Xmm2Log("XMM2", (BYTE*)&p->InExRegs.xmm2);
		Xmm2Log("XMM3", (BYTE*)&p->InExRegs.xmm3);
		Xmm2Log("XMM4", (BYTE*)&p->InExRegs.xmm4);
		Xmm2Log("XMM5", (BYTE*)&p->InExRegs.xmm5);
		Xmm2Log("XMM6", (BYTE*)&p->InExRegs.xmm6);
		Xmm2Log("XMM7", (BYTE*)&p->InExRegs.xmm7);
		pLog->Write("\r\n");
	}
}

void Reg2Log(char* szReg, DWORD reg, char* str){
	pLog->Write("%s %08X", szReg, reg);
	if(str)
		pLog->Write("  \"%s\"\r\n", str);
	else
		pLog->Write("\r\n");
}

void Fpu2Log(char* szReg, BYTE* lp80bitData){
	BYTE dst[100]={0};
	BYTE decim[4]={0};

	decim[0]=8;//after point
	decim[1]=1;//before point

	FpuFLtoA((PBYTE)lp80bitData, (PBYTE)&decim, (PBYTE)&dst, 1024 | 2);
	pLog->Write("%s %s\r\n", szReg, dst);
}

void Mmx2Log(char* szReg, BYTE* lp64bitData){
	pLog->Write("%s ", szReg);
	
	pLog->Write("%02X%02X ", lp64bitData[7], lp64bitData[6]);
	pLog->Write("%02X%02X ", lp64bitData[5], lp64bitData[4]);
	pLog->Write("%02X%02X ", lp64bitData[3], lp64bitData[2]);
	pLog->Write("%02X%02X ", lp64bitData[1], lp64bitData[0]);

	pLog->Write("\r\n");
}

void Xmm2Log(char* szReg, BYTE* lp128bitData){
	pLog->Write("%s ", szReg);

	pLog->Write("%02X%02X%02X%02X ", lp128bitData[15], lp128bitData[14], lp128bitData[13], lp128bitData[12]);
	pLog->Write("%02X%02X%02X%02X ", lp128bitData[11], lp128bitData[10], lp128bitData[9], lp128bitData[8]);
	pLog->Write("%02X%02X%02X%02X ", lp128bitData[7], lp128bitData[6], lp128bitData[5], lp128bitData[4]);
	pLog->Write("%02X%02X%02X%02X ", lp128bitData[3], lp128bitData[2], lp128bitData[1], lp128bitData[0]);
	pLog->Write("\r\n");
}

