
#pragma once

char*	GetHookErrorText(int);
int		IsShortFunc(LPVOID);
WORD	GetLongAnalog(BYTE cc);
void*	GetSafeFuncStart(void *addr);
void*	GetSafeFuncStartOrig(void *addr);

class KHOOK{
	DWORD	code_len;	//Code Len before JMP targ+5
	DWORD	ReassembledCodeLen;
	BYTE	orig_bytes[32];

	DWORD	ReAssembleInstr(BYTE*pBase, BYTE *src, BYTE* dst, DWORD len);

public:
	enum HOOKERRORS{
		PAGE_PROT_ERR=2,
		MEMALLOC_ERR=3,
		LESS_5_BYTE=4
	};

	void* operator new(size_t size, LPCVOID addr, LPCVOID stub, int *pError, DWORD PushID);
	void operator delete(void *);
	LPCVOID	addr;
	LPCVOID	stub;
	BYTE	exec_buf[32];	//reassembled instructions
	BYTE	push_id[16];	//push id; jmp Stub
};
