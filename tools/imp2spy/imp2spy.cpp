#include <windows.h>
#include <commctrl.h>
//#include <dbghelp.h>
#include <delayimp.h>
#include <Imagehlp.h>
#include <TCHAR.H>
#include "resource.h"

#pragma comment(linker,"/MERGE:.rdata=.text")
#pragma comment(lib, "comctl32.lib")
//#pragma	comment(lib, "dbghelp.lib")
#pragma comment(lib, "Imagehlp.lib")

//good PE article http://www.wasm.ru/article.php?article=green2red02
//history
//     .2007 1.0 rustem     author of the tool
//29.01.2011 1.1 sendersu	took orig ver by (c)Rustem, 
//							fixed OriginalFirstThank(if 0), +D-n-D, topmost
//							+imp by ord, +exp by ord & fwd in comments
//30.01.2011 1.2 sendersu   imp/exp by ordinal - fixed output format (func names)
//							if pExport->Name not valid - take input dll name
//01.02.2011 1.3 sendersu	+cmdline support, 
//							+delay import (with rvas flag analysis)
//							check func addr in export, if 0 - skip
//21.05.2011 1.4 sendersu   wow, bug fix in exporter (lots of missed func!)

const TCHAR* APP_NAME = TEXT("imex2spy v1.4");

DWORD ProcessImports(__in HWND, __in LPCTSTR, __in LPCTSTR, __in DWORD, __in DWORD, __in DWORD);
DWORD ProcessExports(__in HWND, __in LPCTSTR, __in LPCTSTR, __in DWORD, __in DWORD);
void UpdateDestEdit(__in HWND, __in TCHAR* src);


LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn;
	BOOL		Trans;
	TCHAR		src[MAX_PATH];
	TCHAR		dst[MAX_PATH];
	DWORD		dwParams;

	switch (message)
	{
	case WM_INITDIALOG:
		{
		CheckRadioButton(hDlg,IDC_IMP,IDC_EXP,IDC_IMP);
		SetDlgItemText(hDlg, IDC_PARAMS, TEXT("3"));
        //DragAcceptFiles(hDlg, TRUE);  
		SetWindowText(hDlg, APP_NAME);

		//check that we have input file in cmd line
		int nArgs=0;
		LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
		if(szArglist && nArgs > 1)
		{
			_tcscpy_s(src, szArglist[1]);
			SetDlgItemText(hDlg, IDC_SRC_PATH, src);
			UpdateDestEdit(hDlg, src);
		}
		LocalFree(szArglist);
		}
		break;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		else if(LOWORD(wParam) == IDC_SRC_SEL){
			ZeroMemory(&ofn, sizeof(ofn));
			ZeroMemory(src, MAX_PATH);
			ofn.lStructSize=sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.hInstance=(HINSTANCE)GetModuleHandle(0);
			ofn.lpstrFilter=TEXT("EXE Files\0*.exe\0DLL Files\0*.dll\0All Files\0*.*\0\0");
			ofn.nMaxFile=MAX_PATH;
			ofn.lpstrFile = src;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if(GetOpenFileName(&ofn)){
				SetDlgItemText(hDlg, IDC_SRC_PATH, src);
				UpdateDestEdit(hDlg, src);
			}
		}
		else if(LOWORD(wParam) == IDC_DST_SEL){
			ZeroMemory(&ofn, sizeof(ofn));
			ZeroMemory(dst, MAX_PATH);
			ofn.lStructSize=sizeof(ofn);
			ofn.hwndOwner = hDlg;
			ofn.hInstance=(HINSTANCE)GetModuleHandle(0);
			ofn.lpstrFilter=TEXT("TXT Files\0*.txt\0All Files\0*.*\0\0");
			ofn.nMaxFile=MAX_PATH;
			ofn.lpstrFile = dst;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_EXPLORER | OFN_LONGNAMES;
			if(GetSaveFileName(&ofn)){
				SetDlgItemText(hDlg, IDC_DST_PATH, dst);
			}
		}
		else if(LOWORD(wParam) == IDGO){
			dwParams=GetDlgItemInt(hDlg, IDC_PARAMS, &Trans, FALSE);
			GetDlgItemText(hDlg, IDC_SRC_PATH, src, MAX_PATH);
			GetDlgItemText(hDlg, IDC_DST_PATH, dst, MAX_PATH);

			if(IsDlgButtonChecked(hDlg, IDC_IMP)==BST_CHECKED){
				if((src[0]==0)||(dst[0]==0)){
					MessageBox(hDlg, TEXT("Select files"), 0, MB_ICONERROR|MB_TOPMOST);
				}
				else{
					DWORD doDelayImp = (IsDlgButtonChecked(hDlg, IDC_IMP_DELAY) == BST_CHECKED);
					DWORD doUnmangle = (IsDlgButtonChecked(hDlg, IDC_UNMANGLE) == BST_CHECKED);
					if(!ProcessImports(hDlg, src, dst, dwParams, doDelayImp, doUnmangle)){
						MessageBox(hDlg, TEXT("DB Created !"), APP_NAME, MB_ICONINFORMATION|MB_TOPMOST);
					}
				}
			}
			else{
				if((src[0]==0)||(dst[0]==0)){
					MessageBox(hDlg, TEXT("Select files"), 0, MB_ICONERROR|MB_TOPMOST);
				}
				else{
					DWORD doUnmangle = (IsDlgButtonChecked(hDlg, IDC_UNMANGLE) == BST_CHECKED);
					if(!ProcessExports(hDlg, src, dst, dwParams, doUnmangle)){
						MessageBox(hDlg, TEXT("DB Created !"), APP_NAME, MB_ICONINFORMATION|MB_TOPMOST);
					}
				}
			}
		}
		else if(LOWORD(wParam) == IDC_OPENDST){
			ZeroMemory(dst, MAX_PATH);
			GetDlgItemText(hDlg, IDC_DST_PATH, dst, MAX_PATH);
			if(dst[0]!=0){
				ShellExecute(0, 0, dst, 0, 0, SW_SHOWMAXIMIZED);
			}
			else{
				MessageBox(hDlg, TEXT("Create DB"), 0, MB_ICONERROR|MB_TOPMOST);
			}
		}
		break;
	case WM_DROPFILES:
			HDROP query = (HDROP) wParam;
			int n=0,count = DragQueryFile( query, NULL, 0, 0 );
			TCHAR file[MAX_PATH];
			DragQueryFile( query, n, file, sizeof(file) );
			DragFinish( query );
			
			SetDlgItemText(hDlg, IDC_SRC_PATH, file);
			UpdateDestEdit(hDlg, file);
		break;
	}
	return FALSE;
}

void UpdateDestEdit(HWND hDlg, TCHAR* src)
{
	TCHAR		dst[MAX_PATH];

	//make default db file as [src].txt
	GetDlgItemText(hDlg, IDC_DST_PATH, dst, MAX_PATH);
	_tcscat_s(src, MAX_PATH, TEXT(".txt"));
	SetDlgItemText(hDlg, IDC_DST_PATH, src);
}

int CALLBACK WinMain(
  __in  HINSTANCE hInstance,
  __in  HINSTANCE hPrevInstance,
  __in  LPSTR lpCmdLine,
  __in  int nCmdShow)
{
	InitCommonControls();
	DialogBox((HINSTANCE)GetModuleHandle(0), (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)MainDlgProc);
	ExitProcess(0);
}


DWORD UnMangleName(__in char* src, __out char* dest, __in int dest_size)
{
		/* todo: 
	  think if you want to undecorate func
	  eg: ??1type_info@@UAE@XZ  => public: virtual __thiscall type_info::~type_info(void)

	  unDName, __unDNameEx from msvcrxx.dll << it does not use UnDecorateSymbolName !
	  http://www.rsdn.ru/forum/?mid=759659
*/
	DWORD undecoratedSymbolCount = 0;
	if ('?' == src[0])
		undecoratedSymbolCount = UnDecorateSymbolName(src, dest, dest_size, UNDNAME_COMPLETE);
	return undecoratedSymbolCount;
}

void UnicodeToAscii(LPCTSTR src, char* szDllA, size_t len)
{
	// Unicode -> char*
	//size_t origsize = wcslen(src) + 1;
	//const size_t newsize = sizeof(szDllA)-1;
	size_t convertedChars = 0;
	wcstombs_s(&convertedChars, szDllA, len, src, _TRUNCATE);
}

void GetDllNameForDb(__in char* szDllA, __out char* szDllDb)
{
	if (!szDllA || !szDllDb)
		return;

	char* p = strrchr(szDllA, '\\');
	strcpy_s(szDllDb, MAX_PATH, (p) ? p+1 : szDllA);
	p = strrchr(szDllDb, '.');
	if (p)
		*p = '\0';
}

DWORD ProcessImports(HWND hDlg, LPCTSTR src, LPCTSTR dst, DWORD dwParams, DWORD doDelayImp, DWORD doUnmangle)
{
	HMODULE hLib = LoadLibraryEx(src, 0, DONT_RESOLVE_DLL_REFERENCES );

	PIMAGE_NT_HEADERS			pHeader			= NULL;
	PIMAGE_IMPORT_DESCRIPTOR	pImport			= NULL;
	PImgDelayDescr				pImportDelay	= NULL;
	PIMAGE_THUNK_DATA			pThunkDataIn	= NULL;
	PIMAGE_THUNK_DATA			pThunkDataOut	= NULL;
	PIMAGE_IMPORT_BY_NAME		pImportByName	= NULL;
	char*						szDll			= NULL;
	char						szDllO[MAX_PATH]= {0};
	DWORD						imageBase		= (DWORD)(DWORD_PTR)hLib;
	DWORD						imageBaseDelta	= 0;
	HANDLE						hOut			= NULL;
	char						buffer[0x400]	= {0};
	char						coment[0x300]	= {0};
	DWORD						dwTemp			= 0;
	BYTE						sz_cr[4]		= {0xD, 0xA, 0, 0};
	DWORD						result			= -1;

	if (hLib){

		hOut=CreateFile(dst, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if(hOut==INVALID_HANDLE_VALUE){
			MessageBox(hDlg, TEXT("Can't open output file"), 0, MB_ICONERROR|MB_TOPMOST);
			goto clean;
		}

		pHeader = ImageNtHeader(hLib);

		if (pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress
			&& pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)
		{
			pImport = (PIMAGE_IMPORT_DESCRIPTOR)(DWORD_PTR)
						(pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress 
						+ imageBase);

			while(pImport->OriginalFirstThunk || pImport->FirstThunk){

				DWORD pThunk = pImport->OriginalFirstThunk ? pImport->OriginalFirstThunk : pImport->FirstThunk;
				szDll = (char*)(imageBase + pImport->Name);
				wsprintfA(buffer, "[%s]", szDll);
				WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);
				WriteFile(hOut, sz_cr, 2, &dwTemp, 0);

				GetDllNameForDb(szDll, szDllO);

				pThunkDataIn  = (PIMAGE_THUNK_DATA)(DWORD_PTR)(pThunk + imageBase);
				pThunkDataOut = (PIMAGE_THUNK_DATA)(DWORD_PTR)(pImport->FirstThunk + imageBase);

				while(pThunkDataIn->u1.Function){	

					if(pThunkDataIn->u1.Ordinal & IMAGE_ORDINAL_FLAG)
					{
						wsprintfA(buffer, "\t!%d , %s_%d , %d", pThunkDataIn->u1.Ordinal & 0xFFFF, 
							szDllO, pThunkDataIn->u1.Ordinal & 0xFFFF, dwParams);
					}
					else
					{
						pImportByName = (PIMAGE_IMPORT_BY_NAME)(DWORD_PTR)(pThunkDataIn->u1.AddressOfData + imageBase);
						int pos = wsprintfA(buffer, "\t%s , %d", pImportByName->Name, dwParams);
						if (doUnmangle && UnMangleName((char*)pImportByName->Name, coment, sizeof(coment))){
							wsprintfA(buffer+pos, "\r\n;%s", coment);
						}
					}

					WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);
					WriteFile(hOut, sz_cr, 2, &dwTemp, 0);

					pThunkDataIn++;
					pThunkDataOut++;
				}
				pImport++;
			}
			result = 0;
		}
		else{
			MessageBox(hDlg, TEXT("No Import"), 0, MB_ICONWARNING|MB_TOPMOST);
		}

		//check if Delayed Import is present, if yes - process
		if (doDelayImp
			&& pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress
			&& pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].Size)
		{
			pImportDelay = (PImgDelayDescr)(DWORD_PTR)
						(pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT].VirtualAddress 
						+ imageBase);

			// check if VC7-style imports, using RVAs instead of
			// VC6-style addresses.
			bool rvas = (pImportDelay->grAttrs & dlattrRva) != 0;
			if (!rvas)
			{
				imageBaseDelta = pHeader->OptionalHeader.ImageBase;
			}

			if (pImportDelay->rvaDLLName){
				wsprintfA(buffer, "\r\n; Delay Import\r\n\r\n");
				WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);
			}

			while(pImportDelay->rvaDLLName){

				DWORD* pThunk = (DWORD*)(imageBase + pImportDelay->rvaINT - imageBaseDelta);

				szDll = (char*)(imageBase + (pImportDelay->rvaDLLName - imageBaseDelta));
				wsprintfA(buffer, "[%s]\r\n", szDll);
				WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);

				GetDllNameForDb(szDll, szDllO);

				while(*pThunk){	

					if(*pThunk & IMAGE_ORDINAL_FLAG) //win64 supp? (diff flag)
					{
						wsprintfA(buffer, "\t!%d , %s_%d , %d", *pThunk & 0xFFFF, 
							szDllO, *pThunk & 0xFFFF, dwParams);
					}
					else
					{
						pImportByName = (PIMAGE_IMPORT_BY_NAME)(DWORD_PTR)(*pThunk + imageBase - imageBaseDelta);
						int pos = wsprintfA(buffer, "\t%s , %d", pImportByName->Name, dwParams);
						if (doUnmangle && UnMangleName((char*)pImportByName->Name, coment, sizeof(coment))){
							wsprintfA(buffer+pos, "\r\n\t;%s", coment);
						}
					}

					WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);
					WriteFile(hOut, sz_cr, 2, &dwTemp, 0);

					pThunk++;
				}
				pImportDelay++;
			}
			result = 0;
		}

		CloseHandle(hOut);
clean:
		FreeLibrary(hLib);
	}
	else{
		MessageBox(hDlg, TEXT("Can't load"), src, MB_ICONERROR|MB_TOPMOST);
	}
	return result;
}


DWORD ProcessExports(HWND hDlg, LPCTSTR src, LPCTSTR dst, DWORD dwParams, DWORD doUnmangle)
{
	PLOADED_IMAGE				pImage			= NULL;
	PIMAGE_NT_HEADERS			pHeader			= NULL;
	PIMAGE_EXPORT_DIRECTORY		pExport			= NULL;
	DWORD						*pFuncNames		= NULL;
	WORD						*pFuncOrdinals	= NULL;
	DWORD						*pFuncAddr		= NULL;
	DWORD						pName			= NULL;
	DWORD						imageBase		= NULL;
	DWORD						dwTemp			= 0;
	HANDLE						hOut			= NULL;
	char						buffer[0x400]	= {0};
	char						coment[0x300]	= {0};
	char						szDllO[MAX_PATH]= {0};
	char						szDllA[MAX_PATH]= {0};
	char*						szDll			= NULL;
	BYTE						sz_cr[4]		= {0xD, 0xA, 0, 0};
	DWORD						result			= -1;

	UnicodeToAscii(src, szDllA, sizeof(szDllA));

	//pImage = ImageLoad(szDllA, NULL);
	HMODULE hLib = LoadLibraryEx(src, 0, DONT_RESOLVE_DLL_REFERENCES);
	//HMODULE hLib = HMODULE(pImage ? pImage->MappedAddress : 0);
	imageBase = (DWORD)(DWORD_PTR)hLib;

	if (hLib){

		pHeader = ImageNtHeader(hLib);

		if (pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress
			&& pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size)
		{
			hOut=CreateFile(dst, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
			if(hOut==INVALID_HANDLE_VALUE){
				MessageBox(hDlg, TEXT("Can't open output file"), 0, MB_ICONERROR|MB_TOPMOST);
				goto clean;
			}

			pExport = (PIMAGE_EXPORT_DIRECTORY)(DWORD_PTR)
					(pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress 
					+ imageBase);

			szDll = (char*)(imageBase + pExport->Name);
			if (!szDll[0])
			{
				//UnicodeToAscii(src, szDllA, MAX_PATH);
				char* p = strrchr(szDllA, '\\');
				szDll = (p) ? p+1 : szDllA;
			}
			GetDllNameForDb(szDll, szDllO);

			wsprintfA(buffer, "[%s]\r\n", szDll);
			WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);

			pFuncOrdinals	=(WORD*)(imageBase + pExport->AddressOfNameOrdinals);
			pFuncNames		=(DWORD*)(imageBase + pExport->AddressOfNames);
			pFuncAddr		=(DWORD*)(imageBase + pExport->AddressOfFunctions);

			DWORD index;
			for (DWORD i=0; i<pExport->NumberOfFunctions; ++i)
			{
				index=~0;
				for (DWORD j=0; j<pExport->NumberOfNames; ++j)
				{
					if (pFuncOrdinals[j] == i){
						index=j;
						break;
					}
				}
				
				*coment = '\0';

				if ((pFuncAddr[i] >= pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress)
					 && (pFuncAddr[i] < pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress
										+pHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size
						)
					 )
				{
					wsprintfA(coment, " ;=> %s", imageBase+pFuncAddr[i]);
				}

				*buffer = '\0';
				if (~0 != index)
				{
					//?tbd this check if (pFuncAddr[index] || *coment){ //*coment means we have redir 
						pName=pFuncNames[index];
						int pos = wsprintfA(buffer, "\t%s , %d%s", imageBase+pName, dwParams, coment);
						if (doUnmangle && UnMangleName((char*)(imageBase+pName), coment, sizeof(coment))){
							wsprintfA(buffer+pos, "\r\n\t\t;%s", coment);
						}
					//}
				}
				else
				{	
					if (pFuncAddr[i]){
						wsprintfA(buffer, "\t!%d , %s_%d , %d%s", pExport->Base+i, 
							szDllO, pExport->Base+i, dwParams, coment);
					}
				}
				
				if (*buffer)
				{
					WriteFile(hOut, buffer, lstrlenA(buffer), &dwTemp, 0);
					WriteFile(hOut, sz_cr, 2, &dwTemp, 0);
				}
			}

			result = 0;
		}
		else{
			MessageBox(hDlg, TEXT("No Export"), 0, MB_ICONWARNING|MB_TOPMOST);
		}

		CloseHandle(hOut);
clean:
		FreeLibrary(hLib);
		//ImageUnload(pImage);
	}
	else{
		MessageBox(hDlg, TEXT("Can't load"), src, MB_ICONERROR|MB_TOPMOST);
	}

	return result;
}
