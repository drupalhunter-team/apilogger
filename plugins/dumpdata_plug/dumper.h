#pragma once

#include <string>
#include <vector>

enum DATA_TYPE;

struct FUNC{
	std::string FuncName;
	DWORD DumpDir;//In/out dump
	
	DWORD DataPointerParamIdx;
	DATA_TYPE DataPointerType;//PBYTE
	
	DWORD LenParamIdx;
	DATA_TYPE LenParamType;//PDWORD, DWORD
};

struct FUNC_CALL{
	FUNC func_db;
	BYTE* pData;
	DWORD Len;
};


enum{
	IN_CHAR=0,
	IN_SPACE=1
};

enum{
	INPUT_DUMP,
	OUTPUT_DUMP
};

enum DATA_TYPE{
	UNKN_TYPE,
	PBYTE_TYPE,
	DWORD_TYPE,
	PDWORD_TYPE
};

DWORD IsSpace(char c, char* szSpac);
char** SplitString(char *s, int *cnt, char* szDelim);
void InitFunctionsDb( HANDLE hDLL );
DATA_TYPE Str2Type( const char* szType );
void DumpBytes( BYTE *data, DWORD Len );
