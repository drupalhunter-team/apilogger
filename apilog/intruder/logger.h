#pragma once

struct	SREGISTERS;
struct	SEXTENDEDREGS;
struct	STHREAD;
class	KHOOK;
struct	KROUTINE;
struct  SPARAM;
struct	SREGSTRINGS;
struct	SPROXYENTRYSTRUCT;


STHREAD* LookUpThread(DWORD tid);

typedef DWORD (__stdcall *PPLUG_BEFORE)(SPROXYENTRYSTRUCT*);
typedef DWORD (__stdcall *PPLUG_AFTER) (SPROXYEXIT*, DWORD);

DWORD	GetLenA(BYTE *p, DWORD maxlen);
DWORD	GetLenW(WORD *p, DWORD maxlen);
char*	GetStrByAddress(BYTE *p, DWORD minlen, DWORD maxlen);
void	GetModuleNameByAddress(DWORD p, char *szName);
DWORD	IsGoodForRead(BYTE *p, DWORD maxlen);
void	Unicode2Ascii(WORD *s, BYTE *d, DWORD len);

void	CollectData2(KROUTINE* p);
void	CleanMemory2(KROUTINE* p);
void	Out2Log2(DWORD tid, KROUTINE *p);

void	Reg2Log(char* szReg, DWORD reg, char* str);
void	Fpu2Log(char* szReg, BYTE* lp80bitData);
void	Mmx2Log(char* szReg, BYTE* lp64bitData);
void	Xmm2Log(char* szReg, BYTE* lp64bitData);


#pragma pack(push,1)
struct SREGISTERS{
	DWORD edi;
	DWORD esi;
	DWORD ebp;
	DWORD esp;
	DWORD ebx;
	DWORD edx;
	DWORD ecx;
	DWORD eax;
	DWORD eflags;
};
#pragma pack(pop)


#pragma pack(push,1)
struct SFUNCTION{
	char*			pName;//function name
	char*           pExtName;
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


#pragma pack(push,1)
struct SSTREG{
	BYTE stdata[10];
};
#pragma pack(pop)


#pragma pack(push,1)
struct S6RES{
	BYTE res[6];
};
#pragma pack(pop)


#pragma pack(push,1)
struct SXMMREG{
	BYTE xmmdata[16];
};
#pragma pack(pop)


#pragma pack(push,1)
__declspec(align(16)) struct SEXTENDEDREGS{
	WORD	fcw;		//0 1
	WORD	fsw;		//2 3
	BYTE	ftw;		//4
	BYTE	empty;		//5
	WORD	fop;		//6 7
	DWORD	fpu_ip;		//8 9 10 11
	WORD	cs_;		//12 13
	WORD	Rsrvd1;		//14 15
	DWORD	fpu_dp;		//16 17 18 19
	WORD	ds_;		//20 21
	WORD	Rsrvd2;		//22 23
	DWORD	mxcsr;		//24 25 26 27
	DWORD	mxsr_mask;	//28 29 30 31
	//st0-st7/mm0-mm7
	SSTREG	st0;		//32
	S6RES	res0;		//
	SSTREG	st1;		//48
	S6RES	res1;		//
	SSTREG	st2;		//64
	S6RES	res2;		//
	SSTREG	st3;		//80
	S6RES	res3;		//
	SSTREG	st4;		//96
	S6RES	res4;		//
	SSTREG	st5;		//112
	S6RES	res5;		//
	SSTREG	st6;		//128
	S6RES	res6;		//
	SSTREG	st7;		//144
	S6RES	res7;		//
	//xmm0-xmm7
	SXMMREG	xmm0;
	SXMMREG	xmm1;
	SXMMREG	xmm2;
	SXMMREG	xmm3;
	SXMMREG	xmm4;
	SXMMREG	xmm5;
	SXMMREG	xmm6;
	SXMMREG	xmm7;

	SXMMREG	res_0;
	SXMMREG	res_1;
	SXMMREG	res_2;
	SXMMREG	res_3;
	SXMMREG	res_4;
	SXMMREG	res_5;
	SXMMREG	res_6;
	SXMMREG	res_7;
	SXMMREG	res_8;
	SXMMREG	res_9;
	SXMMREG	res_10;
	SXMMREG	res_11;
	SXMMREG	res_12;
	SXMMREG	res_13;
};
#pragma pack(pop)


#pragma pack(push,1)
struct SPARAM{
	DWORD param;
	char *str;
};
#pragma pack(pop)


#pragma pack(push,1)
struct SREGSTRINGS{
	char *str_edi;
	char *str_esi;
	char *str_ebp;
	char *str_ebx;
	char *str_edx;
	char *str_ecx;
	char *str_eax;
};
#pragma pack(pop)


#pragma pack(push,1)
struct KROUTINE{
	DWORD	FuncId;
	DWORD	RetAddr;
	DWORD	RetVal;
	DWORD	EnterTime;
	DWORD	LeaveTime;
	LARGE_INTEGER EnterTimeQC;
	LARGE_INTEGER LeaveTimeQC;
	char	szModule[16];
	int		ent;
	int		index;
	SFUNCTION Func;
	DWORD*	pStack;

	//in registers
	SREGISTERS		InRegs;
	SEXTENDEDREGS	InExRegs;
	SREGSTRINGS		InRegStr;
	SPARAM*			pInParams;
	SPARAM          OutVal;
};
#pragma pack(pop)


#pragma pack(push,1)
struct STHREAD{
	DWORD		tid;
	int			store_idx;
	int			cur_tos;
	int			max_tos;
	int			last_index;
	int			MaxDepth;
	KROUTINE*	pStack[MAX_DEPTH];
	KROUTINE*	pStore[MAX_DEPTH];
};
#pragma pack(pop)


enum{
	EXPORT_NAME = 100,
	EXPORT_ORDINAL,
	RVA_ADDR,
	ABSOLUTE_ADDR
};
#pragma pack(push,1)
struct SFUNCDB{
	DWORD       HookType;
	char*       szDllName;
	DWORD       Stuff;

	SFUNCTION	Func;
	KHOOK*		pHook;
	DWORD		FuncAddr;
};
#pragma pack(pop)
