#include "stdafx.h"
#include <Windows.h>

#include "apilog.h"
#include "khook.h"
#include "klog.h"
#include "init.h"
#include "logger.h"
#include "dbparser.h"
#include "commondat.h"


void *KTEXTFILE::operator new(size_t size, char *szFile, int *pError){
	KTEXTFILE *p=(KTEXTFILE*)MemAlloc(sizeof(KTEXTFILE));
	if(!p){
		*pError=MEMALLOC_ERR;
		return 0;
	}

	p->hFile=CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(p->hFile==INVALID_HANDLE_VALUE){
		*pError=FILEOPEN_ERR;
		MemFree(p);
		return 0;
	}

	p->dwFileSize=GetFileSize(p->hFile, 0);
	if(p->dwFileSize==0){
		*pError=ZERO_SIZE;
		CloseHandle(p->hFile);
		MemFree(p);
		return 0;
	}
	
	p->idx=0;
	p->dwTotalReaded=0;
	p->dwCurrentReaded=0;

	return p;
}

BOOL KTEXTFILE::Read2Buffer(){
	memset(buffer, 0, BUFFERSIZE);
	BOOL dwStatus = ReadFile(hFile, buffer, BUFFERSIZE, &dwCurrentReaded, 0);
	dwTotalReaded+=dwCurrentReaded;
	return dwStatus;
}

void KTEXTFILE::operator delete(void *p1){
	KTEXTFILE* p = (KTEXTFILE*)p1;
	if(!p) return;

	MemFree(p);
	CloseHandle(p->hFile);
}

char* KTEXTFILE::ReadLine(){

	//Skip spaces and EOLs in line start
	DWORD	fExit=0;
	DWORD	dwStatus=SKIP_SPACES, dwBuffer=BUFFERSIZE;
	DWORD	dwFreeBytes=dwBuffer, buf_idx=0;
	BOOL	foo=0;
	char	c=0;
	char*	pOutBuf=0;

	do{
		//Read one char
		if(dwCurrentReaded){
			c = buffer[idx];
		}
		else{
			Read2Buffer();
			idx=0;
			if(!dwCurrentReaded){
				fExit=1;
				break;
			}
			continue;
		}

		switch(dwStatus){
		case SKIP_SPACES:
			if(!IsSpace(c) && !IsEOL(c)){
				dwStatus = READ_LINE;
			}
			else{
				dwCurrentReaded--;
				idx++;
			}
			break;

		case READ_LINE:
			if(!pOutBuf) pOutBuf = (char*)MemAlloc(dwBuffer);//First init
			if(dwFreeBytes){
				if(!IsEOL(c)){
					pOutBuf[buf_idx] = c;
					buf_idx++;
					dwFreeBytes--;

					dwCurrentReaded--;
					idx++;
				}
				else{
					fExit=1;
					break;
				}
			}
			else{
				char *pTemp=(char*)MemAlloc(2*dwBuffer);
				memcpy(pTemp, pOutBuf, dwBuffer);
				MemFree(pOutBuf);
				dwFreeBytes =  dwBuffer;
				dwBuffer *= 2;
				pOutBuf = pTemp;
			}
			break;

		default:
			break;
		}
	}while(!fExit);

	return pOutBuf;
}

char** CrackString(char *s, int *cnt){
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
			if(IsSpace(c)){
				state = IN_SPACE;
			}
			else{
				//copy string to buffer
				if(s_idx >= bufsize){//Realloc
					char *pNewStr = (char*)MemAllocTrue(2*bufsize+1);
					memcpy((void*)pNewStr, pStr, bufsize);
					MemFreeTrue(pStr);
					pStr=pNewStr;
					pOut[dwWords-1]=pStr;
					bufsize*=2;
				}
				pStr[s_idx++] = c;
			}
			break;

		case IN_SPACE:
			if(!IsSpace(c)){
				state = IN_CHAR;

				//new word starts here

				//malloc for array of char*
				if(!pOut) pOut = (char**)MemAllocTrue(sizeof(char*));//First init
				else{//Realloc
					char **pNew = (char**)MemAllocTrue((dwWords+1) * sizeof(char*));
					memcpy((void*)pNew, pOut, dwWords*sizeof(char*));
					MemFreeTrue(pOut);
					pOut=pNew;
				}

				if(!pOut[dwWords]){//Alloc for string
					bufsize = 2;//default buffer size

					pOut[dwWords]=(char*)MemAllocTrue(bufsize+1);
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

int IsEOL(char c){
	if(c==0xA || c==0xD || c==0) return 1;
	return 0;
}

int IsSpace(char c){
	if(c==0x20 || c==0x9 || c==',' || c==']') return 1;
	return 0;
}

int IsWhiteSym(char c){
	if(c=='[' || c==']' || c==0x20 || c==0x9 || c==',' || c=='!' || c=='@' || c=='+') return 1;
	return 0;
}

char* CleanString(char *s){
	DWORD i=0;
	char *pOut = 0;

	for(i=0; i < strlen(s); i++){
		if(!IsWhiteSym(s[i])) break;
	}

	DWORD idx=0;
	for(DWORD j=i; j < strlen(s); j++){
		if(!pOut) pOut = (char*)MemAlloc(strlen(s)+1);
		if(!IsSpace(s[j])) pOut[idx++] = s[j];
		else break;
	}
	return pOut;
}

DWORD A2INT(char *s){
	DWORD len = strlen(s);
	DWORD res=0;


	for(DWORD i=0; i<len; i++){
		char c=s[i];
		c -= '0';

		DWORD coef=1;
		if(len-i-1){
			for(int j=0; j<len-i-1; j++) coef*=10;
		}
		res+=c*coef;
	}
	return res;
}

DWORD HEX2DW(char *s){
	DWORD len = strlen(s);
	DWORD res=0;

	for(DWORD i=0; i<len; i++){
		char c=s[i];
		if(c >= '0' && c <= '9') c -= '0';
		else if( c >= 'a' && c <= 'f'){
			c = c - 'a' + 10;
		}
		else if( c>='A' && c <= 'F'){
			c = c - 'A' + 10;
		}

		DWORD coef=1;
		if(len-i-1){
			for(int j=0; j<len-i-1; j++) coef*=16;
		}
		res+=c*coef;
	}
	return res;
}

int FillFunctionOptions(char **p, int dwWords, SFUNCDB* pFuncDB){
	if(dwWords<=1) return 0;

	for(int i=1; i < dwWords; i++){
		if(!strcmp(p[i], TEXT_REG)){
			pFuncDB->Func.fDumpRegs = 1;
		}
		else if(!strcmp(p[i], TEXT_MMX)){
			pFuncDB->Func.fDumpMMX = 1;
		}
		else if(!strcmp(p[i], TEXT_XMM)){
			pFuncDB->Func.fDumpXMM = 1;
		}
		else if(!strcmp(p[i], TEXT_TACTS)){
			pFuncDB->Func.fDumpTacts = 1;
		}
		else if(!strcmp(p[i], TEXT_FPU)){
			pFuncDB->Func.fDumpFpu = 1;
		}
		else if(!strcmp(p[i], TEXT_NOLOG)){
			pFuncDB->Func.fNoLog = 1;
		}
		else if(!strcmp(p[i], TEXT_ECX)){//Dump ECX register value for MSVC compiler (this)
			pFuncDB->Func.fEcx = 1;
		}
		else if(!strcmp(p[i], TEXT_EAX)){//Dump EAX register value for Borland compiler (this)
			pFuncDB->Func.fEax = 1;
		}
		else if(IsNumber(p[i])){//parameters count
			pFuncDB->Func.params = A2INT(p[i]);
		}
		else if(IsFunctionName(p[i])){
			pFuncDB->Func.pName = (char*)MemAlloc(1 + strlen(p[i]));
			memcpy(pFuncDB->Func.pName, p[i], 1 + strlen(p[i]));
		}
	}

	if(settings.Profiler){//If "Profiler" set. Force option in all functions
		pFuncDB->Func.fDumpTacts = 1;
	}
	return 1;
}

int IsNumber(char *s){
	for(int i=0; i < strlen(s); i++){
		char c=s[i];
		if(!(c>='0' && c<='9')) return 0;
	}
	return 1;
}


int IsHexadecimalStr(char *s){
	for(int i=0; i < strlen(s); i++){
		char c=s[i];
		if( !( (c>='a' && c<='f') || (c>='A' && c<='F') || (c>='0' && c<='9') ) ) return 0;
	}
	return 1;
}


//Correct chars 'a'-'z', 'A'-'Z', '@', '?', '_', '$'
int IsFunctionName(char *s){
	for(int i=0; i < strlen(s); i++){
		char c=s[i];
		if(!(c=='$' || c=='@' || c=='?' || c=='_' || (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))) return 0;
	}
	return 1;
}

SFUNCDB* ParseDB(char *szDBFile, DWORD *pFunctions){
	char *pLine=0, *pStr=0;
	char* SZDLL = NULL;
	DWORD dwVal=0;
	int error=0, line=1;
	SFUNCDB funcdb;
	HMODULE  hDLL = 0;
	SFUNCDB* pDB = 0;
	DWORD	FuncsReserve = 1;//reserve functions
	DWORD	FuncsInDB = 0;
	char	szModuleName[64];

	KTEXTFILE *dbfile=new (szDBFile, &error)  KTEXTFILE;
	if(!dbfile){
		str2log("File open error %s\r\n", szDBFile);
		return 0;
	}

	while(1){
		pLine=dbfile->ReadLine();
		if(!pLine) break;

		int dwWords=0;
		char **pp = CrackString(pLine, &dwWords);
		memset(&funcdb, 0, sizeof(funcdb));

		DWORD ExportFunctionFlag = 0;

		if( pp[0][0] == '[' ){//DLL module def. Format is: [user32.dll]
			//pStr = CleanString(pLine);
			pStr = GetDbModuleName(pLine);
			if(pStr){
				hDLL=GetModuleHandle(pStr);
				if( settings.ForceDllLoad && hDLL==0 ){
					hDLL = LoadLibraryA( pStr );
				}
				//Prepare module name
				strcpy(szModuleName, pStr);
				DWORD len=strlen(szModuleName);
				if(szModuleName[len-4]=='.') szModuleName[len-4]=0;//Save for next use
				SZDLL = pStr;
				//str2log("New DLL: %s\r\n", SZDLL);
			}
			else{
				//Error
				str2log("ERROR: Incorrect DLL name (empty name)in line %d\r\n", line);
			}
		}
		else if( pp[0][0] == '!' ){//Format is: !Ordinal, params , NAME_IN_LOG
			pStr = CleanString(pp[0]);
			if(pStr){
				dwVal = HEX2DW(pStr);
				if(dwVal > 0xFFFF){
					//Ordinal range check error
					str2log("ERROR: Ordinal %04X out of range in line %d\r\n", dwVal, line);
				}
				else{
					//Function by ordinal
					//funcdb.FuncAddr = (DWORD)GetProcAddress(hDLL, (LPCSTR)dwVal);
					funcdb.HookType = EXPORT_ORDINAL;
					funcdb.Stuff = dwVal;

					//str2log( "STR %s  ORD: %d\n", pStr, funcdb.Stuff );
					FillFunctionOptions(&pp[0], dwWords, &funcdb);
				}
				MemFree(pStr);
			}
			else{
				//Param not solid error !__NUM
				str2log("ERROR: No parameter in ordinal(space?) in line %d\r\n", line);
			}
		}
		else if( pp[0][0] == '+' ){//Format is: +Value , params , NAME_IN_LOG
			pStr = CleanString(pp[0]);
			if(pStr){
				dwVal = HEX2DW(pStr);
				if(dwVal > 0x7FFFFFFF){
					//Address range check error
					str2log("ERROR: Address range check error in line %d\r\n", line);
				}
				else{
					//Function by relative value
					funcdb.Stuff = dwVal;
					funcdb.HookType = RVA_ADDR;
					FillFunctionOptions(&pp[0], dwWords, &funcdb);
				}
				MemFree(pStr);
			}
			else{
				//Param not solid error +__NUM
				str2log("ERROR: No parameter in relative address(space?) in line %d\r\n", line);
			}
		}
		else if( pp[0][0] == ';' ){//Comment
		}
		else if( pp[0][0] == '@' ){//Format is: @Address , params , NAME_IN_LOG

			pStr = CleanString(pp[0]);
			if( pStr ){
				if( IsHexadecimalStr( pStr ) ){
					dwVal = HEX2DW(pStr);
					if(dwVal > 0x7FFFFFFF || dwVal < 0x10000){
						//Address range check error
						str2log("ERROR: Address range check error in line %d\r\n", line);
					}
					else{
						//Function by absolute address
						funcdb.Stuff = dwVal;
						funcdb.HookType = ABSOLUTE_ADDR;
						FillFunctionOptions(&pp[0], dwWords, &funcdb);
					}
					MemFree(pStr);
				}
				else{//Export Function Name
					ExportFunctionFlag = 1;
					MemFree(pStr);
				}
			}
			else{
				//Param not solid error @__NUM
				str2log("ERROR: No parameter in absolute address(space?) in line %d\r\n", line);
			}
		}
		else{
			ExportFunctionFlag = 1;
		}


		if( ExportFunctionFlag ){//Export Function
			if( IsFunctionName(pp[0]) ){
			    funcdb.HookType = EXPORT_NAME;
				funcdb.Func.pName = (char*)MemAlloc(1 + strlen(pp[0]));
				memcpy(funcdb.Func.pName, pp[0], 1 + strlen(pp[0]));
				FillFunctionOptions(&pp[0], dwWords, &funcdb);
			}
			else{
				//Error in export name
				str2log("ERROR: Incorrect export name %s in line near %d   DLL: %s\r\n", pp[0], line, SZDLL);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////

		funcdb.szDllName = SZDLL;//Save pointer to DLL name
		//Save to db
		if(pp[0][0] != '[' && pp[0][0] != ';' ){
			if(funcdb.Func.pName){
				if( settings.fExtFuncNames && ( funcdb.HookType != ABSOLUTE_ADDR) ){//Use extended names not for all
					DWORD len1=strlen(szModuleName);
					DWORD len2=strlen(funcdb.Func.pName);
					char* pTmpStr = (char*)MemAlloc(len1+len2+2);
					strcpy(pTmpStr, szModuleName);
					strcat(pTmpStr, ".");
					strcat(pTmpStr, funcdb.Func.pName);
					//MemFree(funcdb.Func.pName);
					funcdb.Func.pExtName=pTmpStr;
				}

				//Saving
				if(!pDB){
					pDB = (SFUNCDB*)MemAlloc((FuncsReserve + settings.dwPluginHooks)* sizeof(SFUNCDB));//init array
				}

				if(FuncsInDB >= FuncsReserve){//Realloc
					SFUNCDB* pNew =  (SFUNCDB*)MemAlloc((2 * FuncsReserve + settings.dwPluginHooks) * sizeof(SFUNCDB));
					memcpy(pNew, pDB, FuncsReserve * sizeof(SFUNCDB));
					MemFree(pDB);
					pDB = pNew;
					FuncsReserve *= 2;
				}
				pDB[FuncsInDB] = funcdb;
				FuncsInDB++;
			}
			else{
				str2log("ERROR: Empty function name in line near %d\r\n", line);
			}
		}

		//Free strings
		for(int i=0; i<dwWords; i++){
			MemFree(pp[i]);
		}
		MemFree(pp);//free strings array
		MemFree(pLine);//free readed string
		line++;
	}
	delete dbfile;
	*pFunctions = FuncsInDB;
	return pDB;
}

char* GetDbModuleName(char* s){
	int Found = 0, i=0, j=0;

	for(i = 0; i < strlen(s); i++){
		if(s[i]!='[' && s[i]!=' ' && s[i]!=0x9){
			Found=1;
			break;
		}
	}
	if(Found==0) return 0;

	for(j = i; j < strlen(s); j++){
		if(s[j] == ']' || s[j] == '['){
			break;
		}
	}
	char* pS = (char*)MemAlloc(strlen(s) - i + 1);
	memcpy(pS, &s[i], strlen(s) - i - 1);
	return pS;
}

void ToUpper(char* s){
	// 0x41 - a
	// 0x61 - A
	for(DWORD i=0; i<strlen(s); i++){
		if(s[i]>='a' && s[i]<='z') s[i]&=0x5F;
	}
}

