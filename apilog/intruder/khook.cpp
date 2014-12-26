
#include "stdafx.h"
#include <Windows.h>
#include "khook.h"
#include "hde.h"
#include "apilog.h"
#include "commondat.h"

#pragma comment(lib, "hde.lib")

extern HMODULE g_hKernel32;


char* GetHookErrorText(int Error){
	char *p=0;
	switch(Error){
	case KHOOK::MEMALLOC_ERR:
		p="Mem alloc error";
		break;
	case KHOOK::PAGE_PROT_ERR:
		p="Page protect change error";
		break;
	case KHOOK::LESS_5_BYTE:
		p="Function len less than 5 bytes";
		break;
	default:
		p="Error code out of range";
		break;
	}
	return p;
}

int IsShortFunc(LPVOID addr){
	int res=0;

	DWORD code_len=0;
	BYTE* pcode = (BYTE*)addr;

	while(code_len<5){
		HDE_STRUCT hdestr={0};
		DWORD instr_len=hde_disasm(pcode, &hdestr);
		BYTE Opcode = *pcode;
		code_len += instr_len;
		pcode    += instr_len;
		if(Opcode==0xC3 || Opcode==0xC2){//retn , retn NN
			res=1;
			break;
		}
	}

	if( res == 0 ){//Long function
		return 0;
	}

	if( code_len >= 5 ){//5 bytes len function
		return 0;
	}

	DWORD CheckLen = 5 - code_len;
	DWORD FilledWithCC = 1;
	for( DWORD i = 0; i < CheckLen; i++ ){
		if( (pcode[i] != 0xCC) && (pcode[i] != 0x90) ){//Check for 0xCC or 0x90 after RETN -> compiler code alignment
			FilledWithCC = 0;
		}
	}
	if( FilledWithCC ){
		res = 0;
	}
	return res;
}



void* KHOOK::operator new(size_t size, LPCVOID addr, LPCVOID stub, int *pError, DWORD PushID){
	
	if(IsShortFunc((LPVOID)addr)){
		*pError=LESS_5_BYTE;
		return 0;
	}

	DWORD dwTemp=0;
	if(!safe_VirtualProtectEx((HANDLE)(-1), (LPVOID)addr, 32, PAGE_EXECUTE_READWRITE, &dwTemp)){
		*pError=KHOOK::PAGE_PROT_ERR;
		return 0;
	}

	KHOOK *pHook=(KHOOK*)MemAlloc(sizeof(KHOOK));
	if(!pHook){
		*pError=MEMALLOC_ERR;
		return 0;
	}
	
	pHook->addr=addr;
	pHook->stub=stub;
	pHook->code_len=0;
	pHook->ReassembledCodeLen = 0;

	BYTE* pDst  = (BYTE*)pHook->exec_buf;//dst
	BYTE *pcode = (BYTE*)addr;			//src

	while(pHook->code_len < 5){
		HDE_STRUCT hdestr = {0};
		DWORD instr_len = hde_disasm(pcode, &hdestr);
		
		//reassemble copy
		DWORD NewInstrLen = pHook->ReAssembleInstr((BYTE*)addr, pcode, pDst, instr_len);

		pHook->code_len += instr_len;
		pHook->ReassembledCodeLen += NewInstrLen;
		pcode += instr_len;
		pDst  += NewInstrLen;
	}

	//Save original bytes for restore hook
	memcpy((void*)pHook->orig_bytes, addr, pHook->code_len);


	//push id
	//jmp Stub
	pHook->push_id[0] = 0x68;	//PUSH opcode
	*(DWORD*)&pHook->push_id[1] = PushID;

	pHook->push_id[5] = 0xE9;	//JMP opcode
	*(DWORD*)&pHook->push_id[6] = (DWORD)((BYTE*)stub - ((BYTE*)&pHook->push_id[5] + 5));


	//EXEC_BUFFER...JMP FUNC_ADDR+LEN
	BYTE *dst=pHook->exec_buf + pHook->ReassembledCodeLen;
	*(BYTE*)dst = 0xE9;//JMP opcode
	*(DWORD*)(dst+1) = (DWORD)((DWORD)((BYTE*)addr + pHook->code_len) - (DWORD)dst - 5);


	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Set hook
	//Write jmp stub to function begin address
	*(BYTE*)addr=0xE9;
	if(PushID==0xFFFFFFFF){//jmp to exec_buf
		*(DWORD*)((BYTE*)addr + 1)=(DWORD)((BYTE*)stub - ((BYTE*)addr + 5));
	}
	else{// jmp to pushid
		*(DWORD*)((BYTE*)addr + 1)=(DWORD)((BYTE*)(BYTE*)pHook->push_id - ((BYTE*)addr + 5));
	}
	
	
	if(!safe_VirtualProtectEx((HANDLE)(-1), (LPVOID)pHook->exec_buf, 32, PAGE_EXECUTE_READWRITE, &dwTemp)){
		*pError=KHOOK::PAGE_PROT_ERR;
		return 0;
	}

	if(!safe_VirtualProtectEx((HANDLE)(-1), (LPVOID)pHook->push_id, 16, PAGE_EXECUTE_READWRITE, &dwTemp)){
		*pError=KHOOK::PAGE_PROT_ERR;
		return 0;
	}

	//safe_FlushInstructionCache((HANDLE)-1, 0, 0);
	return pHook;
}


void KHOOK::operator delete(void *p){
	if(!p) return;

	KHOOK *pHook=(KHOOK*)p;
	memcpy((void*)pHook->addr, pHook->orig_bytes, pHook->code_len);
	//safe_FlushInstructionCache((HANDLE)-1, 0, 0);
	MemFree(p);
}

DWORD KHOOK::ReAssembleInstr(BYTE* Base, BYTE *src, BYTE* dst, DWORD len){
	DWORD retlen=len;

	if(*src==0xE8 || *src==0xE9){//CALL or JMP
		int src_addr = (int)src;
		int Operand  = *(int*)&src[1];
		int dst_addr = src_addr + Operand + 5;

		*dst = *src;	//copy instruction opcode
		*(DWORD*)&dst[1] = (DWORD)dst_addr - (DWORD)dst - 5;
	}
	else if( *src >= 0x70 && *src <= 0x7F ){//Short JXX instruction
		DWORD src_addr = (DWORD)src;
		char Operand  = *(char*)&src[1];
		DWORD dst_addr = src_addr + Operand + 2;

		if(dst_addr > (DWORD)Base + 5){//FIX: OPERAND RANGE CHECK
			*(WORD*)&dst[0]=GetLongAnalog(src[0]);
			*(DWORD*)&dst[2] = (DWORD)dst_addr - (DWORD)dst - 6;
			retlen = 6;//instr len
		}
		else{//jmp in 5 byte block - copy without changes
			memcpy(dst, src, len);
		}
	}
	else if( *src==0xEB ){//JMP SHORT-> JMP LONG
		DWORD src_addr = (DWORD)src;
		char Operand  = *(char*)&src[1];
		DWORD dst_addr = src_addr + Operand + 2;

		if(dst_addr > (DWORD)Base + 5){//FIX: OPERAND RANGE CHECK
			*dst = 0xE9;
			*(DWORD*)&dst[1] = (DWORD)dst_addr - (DWORD)dst - 5;
			retlen = 5;
		}
		else{
			memcpy(dst, src, len);
		}
	}
	else{
		memcpy(dst, src, len);
	}
	return retlen;
}

WORD GetLongAnalog(BYTE cc){
	WORD r=0;

	//75 -> 85 0F
	r = 0x800F;

	r |= (cc & 0x0F)<<8;
	
	return r;
};

//Creates stub function. And jump to target+5 bytes
void* GetSafeFuncStart(void *addr){
	//malloc for code
	void *p=MemAlloc(32);
	if(!p) return 0;

	DWORD dwTemp;
	safe_VirtualProtectEx((HANDLE)(-1), (LPVOID)p, 32, PAGE_EXECUTE_READWRITE, &dwTemp);	
	
	BYTE *pcode=(BYTE*)addr;
	DWORD code_len=0;
	while(code_len<5){
		HDE_STRUCT hdestr={0};
		DWORD instr_len=hde_disasm(pcode, &hdestr);
		code_len+=instr_len;
		pcode+=instr_len;
		//FIX: opcode tests here
	}
	memcpy((void*)p, addr, code_len);
	pcode=(BYTE*)p+code_len;
	*pcode=0xE9;
	*(DWORD*)(pcode+1)=(DWORD)((DWORD)((BYTE*)addr+code_len)-(DWORD)pcode-5);
	return p;
}

//Creates stub function. And jump to target+5 bytes
void* GetSafeFuncStartOrig(void *addr){
	//malloc for code
	void *p = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 32);
	if(!p) return 0;

	//Damn antivirals trick
	PFN_VirtualProtectEx pVirtualProtectEx = (PFN_VirtualProtectEx)(GetProcAddress( g_hKernel32, "VirtualProtectEx" ) );

	DWORD dwTemp;
	pVirtualProtectEx((HANDLE)(-1), (LPVOID)p, 32, PAGE_EXECUTE_READWRITE, &dwTemp);	

	BYTE *pcode=(BYTE*)addr;
	DWORD code_len=0;
	while(code_len<5){
		HDE_STRUCT hdestr={0};
		DWORD instr_len=hde_disasm(pcode, &hdestr);
		code_len+=instr_len;
		pcode+=instr_len;
		//FIX: opcode tests here
	}
	memcpy((void*)p, addr, code_len);
	pcode=(BYTE*)p+code_len;
	*pcode=0xE9;
	*(DWORD*)(pcode+1)=(DWORD)((DWORD)((BYTE*)addr+code_len)-(DWORD)pcode-5);
	return p;
}
