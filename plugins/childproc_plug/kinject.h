#pragma once

void EnableDebugPriv(void);

class KInject{
	BOOL WINAPI InjectLibW(DWORD, PCWSTR);
	BOOL WINAPI InjectLibA(DWORD, PCSTR);

	void InjectDll(HANDLE hProcess, HANDLE hThread, DWORD param);
public:
	void Inject2(HANDLE hProcess, HANDLE hThread);
	int CreateAndInject2Process(LPCTSTR, LPCTSTR, LPCTSTR, LPCTSTR);
	BOOL Inject2Process(DWORD, LPCTSTR);
};

#ifdef UNICODE
#define InjectLib  InjectLibW
#else
#define InjectLib  InjectLibA
#endif // !UNICODE
