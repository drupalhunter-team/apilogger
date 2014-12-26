#pragma once

#define CACHE_SIZE 16384

char* GetLogErrorText(int err);

class KLOG{
	char	cache[CACHE_SIZE];
	DWORD	dwFlags;
	HANDLE	hFile;
	DWORD	dwOffset;
	void	FlushCache();

public:
	enum{
		MEMALLOC_ERR=1,
		FILEOPEN_ERR=2
	};
	void	*operator new(size_t size, char *szFile, DWORD dwFlags, int *pError);
	void	operator delete(void *);
	void	Write(char *fmt, ...);
	void	WriteTimeStr();
	void	Output(char *s);
};
