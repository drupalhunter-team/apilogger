#pragma once

#define BUFFERSIZE 3

#define TEXT_REG	"#reg"
#define TEXT_TACTS	"#tacts"
#define TEXT_FPU	"#fpu"
#define TEXT_MMX	"#mmx"
#define TEXT_XMM	"#xmm"
#define TEXT_NOLOG	"#nolog"
#define TEXT_ECX	"#ecx"
#define TEXT_EAX	"#eax"

enum{
	SKIP_SPACES=0,
	READ_LINE=1
};

enum{
	IN_CHAR=0,
	IN_SPACE=1
};

class KTEXTFILE{
	int		idx;
	HANDLE	hFile;
	DWORD	dwFileSize;
	DWORD	dwTotalReaded;
	DWORD	dwCurrentReaded;
	char	buffer[BUFFERSIZE];
	BOOL	Read2Buffer();
public:
	enum{
		MEMALLOC_ERR=1,
		FILEOPEN_ERR=2,
		ZERO_SIZE=3
	};

	char*	ReadLine();
	void	*operator new(size_t size, char *szFile, int *pError);
	void	operator delete(void *);
};

int		IsEOL(char c);
int		IsSpace(char c);
int		IsWhiteSym(char c);
DWORD	A2INT(char *s);
DWORD	HEX2DW(char *s);
char**	CrackString(char *s, int *cnt);
char*	CleanString(char *s);
int		FillFunctionOptions(char **p, int dwWords, SFUNCDB* funcdb);
int		IsFunctionName(char *s);
int		IsNumber(char *s);

SFUNCDB* ParseDB(char *szDBFile, DWORD *FuncsCnt);
char* GetDbModuleName(char* s);
void ToUpper(char* s);
