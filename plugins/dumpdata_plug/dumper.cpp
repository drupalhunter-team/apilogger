
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "dumper.h"
#include "plugin.h"

extern std::vector < FUNC > g_FunctionsDb;
extern std::vector < FUNC_CALL > g_FunctionsCall;

char* GetOptionStr( char* pApp, char* pKey, char* pDef, char* pFileName ){
	DWORD BufSize = 0x40;
	char* p = (char*)malloc(BufSize);
	while(1){
		DWORD Retv = GetPrivateProfileString( pApp, pKey, pDef, p, BufSize, pFileName );
		if(Retv != BufSize-1 && Retv != BufSize-2){
			return p;
		}
		BufSize *= 2;
		p = (char*)realloc(p, BufSize);
	}
}

DATA_TYPE Str2Type( const char* szType ){
	if( strcmp( szType, "DWORD" )==0 ){
		return DWORD_TYPE;
	}
	else if( strcmp( szType, "PBYTE" )==0 ){
		return PBYTE_TYPE;
	}
	else if( strcmp( szType, "PDWORD" )==0 ){
		return PDWORD_TYPE;
	}
	UNKN_TYPE;
}


void InitFunctionsDb( HANDLE hDLL ){
	char szBuf[MAX_PATH];
	GetModuleFileName((HMODULE)hDLL, szBuf, MAX_PATH);
	for(DWORD i = strlen(szBuf); i>0; i--){if(szBuf[i]=='\\'){szBuf[i]=0; break;}}
	strcat( szBuf, "\\funcs.ini" );
	//Logger( "INI ===> %s\r\n", szBuf );


	char szFunc[100];

	int j = 0;
	while(1){
		sprintf( szFunc, "f%d", j++ );
		char* szFuncParams = GetOptionStr( "functions", szFunc, "funcnotfound", szBuf );
		if( strcmp( szFuncParams, "funcnotfound" )== 0 ){
			break;
		}

		int cnt;
		char** pTemp = SplitString( szFuncParams, &cnt, ",; ");
//		Logger( "PARAM_STR ===> %s\r\n", szFuncParams );
//		for( int i=0; i<cnt; i++ ){
//			Logger( "PARAMS DUMP: %i - %s\r\n", i, pTemp[i] );
//		}
		if( cnt == 6 ){
			FUNC funcdef;
			funcdef.FuncName = pTemp[0];//0 - name
			if( strcmp( pTemp[1], "OUT" ) == 0 ){ funcdef.DumpDir = OUTPUT_DUMP; }
			else{ funcdef.DumpDir = INPUT_DUMP; }

			funcdef.DataPointerParamIdx = atoi    ( pTemp[2] );
			funcdef.DataPointerType     = Str2Type( pTemp[3] );

			funcdef.LenParamIdx         = atoi    ( pTemp[4] );
			funcdef.LenParamType        = Str2Type( pTemp[5] );
			g_FunctionsDb.push_back( funcdef );
		}
		else{
			Logger( "Error in function def\r\n" );
		}
	}
}




DWORD IsSpace(char c, char* szSpac){
	for(DWORD i = 0; i < strlen(szSpac); i++){
		if(c == szSpac[i])
			return 1;
	}
	return 0;
}

char** SplitString(char *s, int *cnt, char* szDelim){
	DWORD state = IN_SPACE;
	DWORD dwWords = 0, dwMaxWords=2;
	char c=0;

	*cnt = 0;
	char** pOut=0;
	DWORD bufsize=0;
	char *pStr=0;
	DWORD s_idx=0;

	if(strlen(s)==0) return 0;

	for(DWORD i = 0; i < strlen(s); i++){
		c = s[i];

		switch(state){
		case IN_CHAR:
			if(IsSpace(c, szDelim)){
				state = IN_SPACE;
			}
			else{
				//copy string to buffer
				if(s_idx >= bufsize){//Realloc
					char *pNewStr = (char*)calloc(2*bufsize+1, 1);
					memcpy((void*)pNewStr, pStr, bufsize);
					free(pStr);
					pStr=pNewStr;
					pOut[dwWords-1]=pStr;
					bufsize*=2;
				}
				pStr[s_idx++] = c;
			}
			break;

		case IN_SPACE:
			if(!IsSpace(c, szDelim)){
				state = IN_CHAR;

				//new word starts here

				//malloc for array of char*
				if(!pOut) pOut = (char**)calloc(sizeof(char*)*2, 1);//First init
				else{//Realloc
					char **pNew = (char**)calloc((dwWords+2) * sizeof(char*), 1);
					memcpy((void*)pNew, pOut, dwWords*sizeof(char*));
					free(pOut);
					pOut=pNew;
				}

				if(!pOut[dwWords]){//Alloc for string
					bufsize = 2;//default buffer size

					pOut[dwWords]=(char*)calloc(bufsize+1, 1);
					pStr=pOut[dwWords];
					s_idx=0;

					pStr[s_idx++] = c;
					dwWords++;//words count
				}
			}
			break;

		default:
			break;

		}
	}
	*cnt=dwWords;
	return pOut;
}



void DumpBytes( BYTE *data, DWORD Len ){
	if(Len==0 || Len==0xFFFFFFFF)
		return;

	DWORD len = Len;

	//Part 0
	Logger("pdata: %08X Len: %08X  -> ",data, Len);
	for(DWORD  j = 0; j < Len; j++){ 
		char b=(char)data[j];
		Logger("%02X ", b);
	}
	Logger( "     " );

	for(DWORD  j = 0; j < Len; j++){ 
		char b=(char)data[j];
		if((b >= 0x20) && (b < 0x7F)){
			Logger("%c", b);
		}
		else{
			Logger("%c", '.');
		}
	}
	Logger("\r\n");

}
