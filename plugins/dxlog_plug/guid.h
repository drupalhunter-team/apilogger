#pragma once
void	HookByIID(LPCVOID pIID, LPCVOID pObj);
DWORD	GetMethodAddr(DWORD **pvtbl, DWORD idx);

#pragma pack(push,1)
struct MYGUID{
	DWORD	x0;
	WORD	x1;
	WORD	x2;
	BYTE	x3_0;
	BYTE	x3_1;
	BYTE	x3_2;
	BYTE	x3_3;
	BYTE	x3_4;
	BYTE	x3_5;
	BYTE	x3_6;
	BYTE	x3_7;
};
#pragma pack(pop)
