
#include "stdafx.h"
#include <Windows.h>

#include "klog.h"
#include "apilog.h"
#include "init.h"
#include "commondat.h"

extern HMODULE g_hKernel32;

//Flags:
//7 6 5 4 3 2 1 0
//            | |
//            | FileLog (1-on)
//            |
//            Cache log(1-cache on)
//          
//          
//
void* KLOG::operator new(size_t size, char *szFile, DWORD dwFlags, int *pError){
	KLOG *p=(KLOG*)MemAlloc(sizeof(KLOG));
	if(!p){
		*pError=MEMALLOC_ERR;
		return 0;
	}
	p->dwFlags=dwFlags;
	p->dwOffset=0;
	p->hFile=0;
	if(dwFlags & 1){//if log on-open log file
		p->hFile=CreateFileA(szFile, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(p->hFile==INVALID_HANDLE_VALUE){
			*pError=FILEOPEN_ERR;
			MemFree(p);
			return 0;
		}
	}
	return p;
}

void KLOG::operator delete(void *p){
	if(!p) return;

	KLOG *pLog=(KLOG*)p;
	if(pLog->hFile){
		pLog->FlushCache();
		safe_CloseHandle(pLog->hFile);
	}
	MemFree(p);
}

void KLOG::FlushCache(){
	DWORD dwTemp=0;
	if(!hFile) return;

	if(dwOffset){
		safe_WriteFile(hFile, cache, dwOffset, &dwTemp, 0);
		dwOffset=0;
	}
}

void KLOG::Output(char *s){
	if(!hFile) return;//nothing to do

	DWORD dwTemp=0;
	size_t len=strlen(s);

	if(dwFlags & 2){//Cache option
		if(dwOffset+len>=CACHE_SIZE){// flush data to file
			FlushCache();
			if(len>CACHE_SIZE){//str len much than cache size
				safe_WriteFile(hFile, s, len, &dwTemp, 0);
			}
			else{//copy str to buffer
				strcpy(cache, s);
				dwOffset=len;
			}
		}
		else{//copy string to cache
			cache[dwOffset]='\0';//sz
			strcat(cache, s);
			dwOffset+=len;
		}
	}
	else{//No cache option. Write to file
		safe_WriteFile(hFile, s, len, &dwTemp, 0);	
	}
}

void KLOG::Write(PCHAR fmt, ...){
	char buffer[1024];

	va_list ap;
	va_start(ap, fmt);
	safe_wvsprintfA(buffer, fmt, ap);
	Output(buffer);
	va_end(ap);
}

char* GetLogErrorText(int err){
	char *p=0;
	switch(err){
	case KLOG::FILEOPEN_ERR:
		p="Can't open file";
	break;

	case KLOG::MEMALLOC_ERR:
		p="Mem alloc error";
	break;
	default:
		p="Error code out of range";
	break;
	}
	return p;
}

void KLOG::WriteTimeStr(){
	char* day[]={"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	char* month[]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	SYSTEMTIME t;
	GetLocalTime(&t);

	str2log("%s %s %d %d:%02d:%02d %d\r\n", day[t.wDayOfWeek], month[t.wMonth-1], t.wDay, t.wHour, t.wMinute,  t.wSecond, t.wYear);
}
