#include "stdafx.h"
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <psapi.h>
#include <commctrl.h>
#include <shlobj.h>
#include <ShellAPI.h>
#include <shlwapi.h>
#include "resource.h"
#include "kinject.h"
#include "proclist.h"
#include <stdio.h>
#include "injector.h"
#include "gui.h"
#include "resource.h"

extern DWORD InjType;	//0-create new, 1-attach
extern DWORD dwPid;		//Attach Process PID

BOOL CreateToolTip(int toolID, HWND hDlg, TCHAR* pText){
	// toolID:  the resource ID of the control.
	// hDlg:    the handle of the dialog box.
	// pText:   the text that appears in the tooltip.
	// g_hInst: the global instance handle.


	if (!toolID || !hDlg || !pText)
	{
		return FALSE;
	}
	// Get the window of the tool.
	HWND hwndTool = GetDlgItem(hDlg, toolID);

	// Create the tooltip.
	HWND hwndTip = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
		WS_POPUP |TTS_ALWAYSTIP | TTS_BALLOON,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		hDlg, NULL, 
		GetModuleHandle(0), NULL);

	if (!hwndTool || !hwndTip)
	{
		return FALSE;
	}                              

	// Associate the tooltip with the tool.
	TOOLINFO toolInfo = { 0 };
	toolInfo.cbSize = sizeof(toolInfo);
	toolInfo.hwnd = hDlg;
	toolInfo.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	toolInfo.uId = (UINT_PTR)hwndTool;
	toolInfo.lpszText = pText;
	SendMessage(hwndTip, TTM_ADDTOOL, 0, (LPARAM)&toolInfo);

	return TRUE;
}

void MainInit(HWND hDlg){
	TCHAR	szDLL[MAX_PATH];
	TCHAR	szBuf[MAX_PATH];
	TCHAR	szBuf2[MAX_PATH];

	EnableWindow(GetDlgItem(hDlg, IDC_RUN), FALSE);
	EnableWindow(GetDlgItem(hDlg, ID_OPENLOG), FALSE);

	//Main tooltips create
	CreateToolTip(ID_SEL_EXE,   hDlg, TEXT("Select EXE file"));
	CreateToolTip(ID_ATTACH,    hDlg, TEXT("Select process to attach"));
	CreateToolTip(IDC_ARGS,     hDlg, TEXT("Command line arguments for new process"));
	CreateToolTip(IDC_STARTDIR, hDlg, TEXT("Work directory for new process"));

	//Default database "path\db.txt"
	GetModuleFileName((HMODULE)0, szBuf2, MAX_PATH-1);
	for(DWORD i=(DWORD)lstrlen(szBuf2); i>0; i--){if(szBuf2[i-1]=='\\'){szBuf2[i]=0; break;}}
	lstrcat(szBuf2, TEXT("db.txt"));

	GetIniPath(szBuf, MAX_PATH);
	GetPrivateProfileString(TEXT("Settings"), TEXT("DBFile"), szBuf2, szDLL, MAX_PATH, szBuf);
	//DATABASE FULL PATH!!!
	if(szDLL[0]){
		SetDlgItemText(hDlg, IDC_DB, szDLL);
	}
	else{
		SetDlgItemText(hDlg, IDC_DB, szBuf2);
	}


	//Target exe
	GetPrivateProfileString(TEXT("Settings"), TEXT("Target"), TEXT(""), szDLL, MAX_PATH, szBuf);
	if(szDLL[0]){
		if(StrCmpNIW(szDLL, TEXT("PID :"), 5)){
			SetDlgItemText(hDlg, IDC_EXENAME, szDLL);

			//Out log file
			GetPrivateProfileString(TEXT("Settings"), TEXT("OutLogFile"), TEXT(""), szDLL, MAX_PATH, szBuf);
			if(szDLL[0]){
				SetDlgItemText(hDlg, IDC_OUTFILE, szDLL);

				WIN32_FIND_DATA fd={0};
				HANDLE fh = FindFirstFile(szDLL, &fd);
				if(fh != INVALID_HANDLE_VALUE){
					EnableWindow(GetDlgItem(hDlg, ID_OPENLOG), TRUE);
					FindClose(fh);
				}
			}

			//Args
			GetPrivateProfileString(TEXT("Settings"), TEXT("Args"), TEXT(""), szDLL, MAX_PATH, szBuf);
			if(szDLL[0]){
				SetDlgItemText(hDlg, IDC_ARGS, szDLL);
			}

			//Work dir
			GetPrivateProfileString(TEXT("Settings"), TEXT("WorkDir"), TEXT(""), szDLL, MAX_PATH, szBuf);
			if(szDLL[0]){
				SetDlgItemText(hDlg, IDC_STARTDIR, szDLL);
			}

			InjType=0;
			SetDlgItemText(hDlg, IDC_RUN, TEXT("Run"));
			EnableWindow(GetDlgItem(hDlg, IDC_RUN), TRUE);
		}
	}

	HICON hIco = LoadIcon(GetModuleHandle(0), (LPCWSTR)IDI_ICON1);
	PostMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIco );
	SetFocus(GetDlgItem(hDlg, ID_SEL_EXE));
}


void MainOptions(HWND hDlg){
	TCHAR	szDLL[MAX_PATH];
	GetModuleFileName(0, szDLL, MAX_PATH);
	for(DWORD i=(DWORD)lstrlen(szDLL); i>0; i--){if(szDLL[i-1]==TEXT('\\')){szDLL[i]=0; break;}}
	lstrcat(szDLL, TEXT("settings.ini"));

	WIN32_FIND_DATA fd; 
	HANDLE hFile = FindFirstFile(szDLL, &fd);
	if(hFile==INVALID_HANDLE_VALUE){
		MessageBox(0, TEXT("settings.ini not found"), 0, MB_ICONSTOP|MB_TOPMOST);
	}
	else{
		FindClose(hFile);
		DialogBox((HINSTANCE)GetModuleHandle(0), (LPCTSTR)IDD_DIALOG3, hDlg, (DLGPROC)DlgSettings);
	}
}


void MainSelectExe(HWND hDlg){
	OPENFILENAME ofn;
	TCHAR	szExe[MAX_PATH];
	TCHAR	szBuf2[MAX_PATH];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner = hDlg;
	ofn.hInstance=(HINSTANCE)GetModuleHandle(0);
	ofn.lpstrFilter=TEXT("EXE Files\0*.exe\0DLL Files\0*.dll\0All Files\0*.*\0\0");
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFile = szExe;
	ofn.lpstrFile[0]='\0';

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if(GetOpenFileName(&ofn)){
		InjType=0;
		SetDlgItemText(hDlg, IDC_RUN, TEXT("Run"));
		SetDlgItemText(hDlg, IDC_EXENAME, szExe);
		EnableWindow(GetDlgItem(hDlg, IDC_RUN), TRUE);

		EnableWindow(GetDlgItem(hDlg, IDC_ARGS), TRUE);
		EnableWindow(GetDlgItem(hDlg, IDC_STARTDIR), TRUE);

		//Work Directory Set
		lstrcpy(szBuf2, szExe);
		for(DWORD i=(DWORD)lstrlen(szBuf2); i>0; i--){if(szBuf2[i-1]==TEXT('\\')){szBuf2[i]=0; break;}}
		SetDlgItemText(hDlg, IDC_STARTDIR, szBuf2);

		SetOutFile(hDlg, szExe);
	}
}

static TCHAR szLOG[MAX_PATH];
void InjRun(HWND hDlg){
	TCHAR	szDLL[MAX_PATH];
	TCHAR	szArgs[MAX_PATH];
	TCHAR	szDir[MAX_PATH];
	TCHAR	szExe[MAX_PATH];
	TCHAR	szBuf[MAX_PATH];

	KInject inj;

	GetDlgItemText(hDlg, IDC_OUTFILE, szBuf, MAX_PATH);
	if(!szBuf[0]){
		MessageBox(hDlg, TEXT("Select output file"), 0, MB_ICONERROR|MB_TOPMOST);
		return;
	}

	GetDlgItemText(hDlg, IDC_DB, szBuf, MAX_PATH);
	if(!szBuf[0]){
		MessageBox(hDlg, TEXT("Select database file"), 0, MB_ICONERROR|MB_TOPMOST);
		return;
	}

	GetDlgItemText(hDlg, IDC_EXENAME, szBuf, MAX_PATH);
	if(!szBuf[0]){
		MessageBox(hDlg, TEXT("Select target file/process"), 0, MB_ICONERROR|MB_TOPMOST);
		return;
	}

	//Save paths in ini
	SavePath(hDlg);

	//Exe full path
	ZeroMemory(szExe,  MAX_PATH);
	GetDlgItemText(hDlg, IDC_EXENAME, szExe, MAX_PATH);

	//Intruder.dll full path
	GetModuleFileName(0, szDLL, MAX_PATH);
	for(DWORD i=(DWORD)lstrlen(szDLL); i>0; i--){if(szDLL[i-1]==TEXT('\\')){szDLL[i]=0; break;}}
	lstrcat(szDLL, TEXT("intruder.dll"));

	if(szExe[0]!=0 && InjType==0){
		DWORD len = lstrlen(szExe);
		if(!lstrcmpi(&szExe[len-4], TEXT(".dll"))){
			MessageBox(hDlg, TEXT("Load DLL"), TEXT("API Logger"), MB_ICONEXCLAMATION | MB_TOPMOST);

			LoadLibrary(szDLL);	//intruder.dll
			LoadLibrary(szExe);	//Target DLL
			ExitProcess(0);		//ExitProcess
		}
		else{
			ZeroMemory(szArgs, MAX_PATH);
			ZeroMemory(szDir,  MAX_PATH);
			GetDlgItemText(hDlg, IDC_ARGS, szArgs, MAX_PATH);
			GetDlgItemText(hDlg, IDC_STARTDIR, szDir, MAX_PATH);

			GetIniPath(szBuf, MAX_PATH);
			//CREATE REMOTE THREAD
			if(inj.CreateAndInject2Process(szExe, szArgs, szDLL, szDir)!=0){
				MessageBox(hDlg, TEXT("Inject Failed"), 0, MB_ICONERROR | MB_TOPMOST);
			}
			else{
				EnableWindow(GetDlgItem(hDlg, IDC_OPENLOG), TRUE);

				//Check for LogFile="" in settings.ini
				//Log File Path
				GetDlgItemText(hDlg, IDC_EXENAME, szLOG, 260);
				DWORD len = lstrlen(szLOG);
				if(szLOG[len-4]==TEXT('.')) szLOG[len-4]=TEXT('\0');
				lstrcat(szLOG, TEXT(".apilog.txt"));
			}
		}
	}
	else if(InjType==1 && dwPid != -1){//Attach to process selected
		if(inj.Inject2Process(dwPid, szDLL)){
			MessageBox(hDlg, TEXT("Attach to process failed"), 0, MB_ICONERROR | MB_TOPMOST);
		}
		else{
			EnableWindow(GetDlgItem(hDlg, IDC_OPENLOG), TRUE);
			PFN_OpenProcess pOpenProcess = (PFN_OpenProcess)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "OpenProcess" ) );

			//Check for LogFile="" in settings.ini
			//
			HANDLE hProcess = pOpenProcess(PROCESS_ALL_ACCESS, 0, dwPid);
			HMODULE hPSAPI = LoadLibraryA("psapi.dll");
			PFN_GetModuleFileNameEx pGetModuleFileNameEx = (PFN_GetModuleFileNameEx)(GetProcAddress( hPSAPI, "GetModuleFileNameExW" ) );
			pGetModuleFileNameEx(hProcess, 0, szLOG, MAX_PATH);
			CloseHandle(hProcess);
			DWORD len = lstrlen(szLOG);
			if(szLOG[len-4]=='.') szLOG[len-4]='\0';
			lstrcat(szLOG, TEXT(".apilog.txt"));
		}
	}
	else{
		MessageBox(hDlg, TEXT("Select EXE or DLL or Attach To Process"), 0, MB_ICONERROR|MB_TOPMOST);
	}
}


void Attach(HWND hDlg){
	TCHAR	szBuf[MAX_PATH];
	
	dwPid=-1;
	//Processes list
	DialogBox(GetModuleHandle(0), (LPCTSTR)IDD_DIALOG2, hDlg, (DLGPROC)ProcessDlgProc);
	if(dwPid != -1){//Process selected

		InjType=1; //Type == Attach to Process
		SetDlgItemText(hDlg, IDC_RUN, TEXT("Attach"));
		wsprintf(szBuf, TEXT("PID : %d"), dwPid);

		SetDlgItemText(hDlg, IDC_EXENAME, szBuf);
		EnableWindow(GetDlgItem(hDlg, IDC_RUN), TRUE);

		SetDlgItemText(hDlg, IDC_ARGS, TEXT(""));
		SetDlgItemText(hDlg, IDC_STARTDIR, TEXT(""));
		EnableWindow(GetDlgItem(hDlg, IDC_ARGS), FALSE);
		EnableWindow(GetDlgItem(hDlg, IDC_STARTDIR), FALSE);

		//DebugBreak();
		szBuf[0]=0;
		//Output file
		PFN_OpenProcess pOpenProcess = (PFN_OpenProcess)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "OpenProcess" ) );
		HANDLE h = pOpenProcess(PROCESS_ALL_ACCESS, NULL, dwPid);

		HMODULE hPSAPI = LoadLibraryA("psapi.dll");
		PFN_GetModuleFileNameEx pGetModuleFileNameEx = (PFN_GetModuleFileNameEx)(GetProcAddress( hPSAPI, "GetModuleFileNameExW" ) );
		DWORD xx = pGetModuleFileNameEx(h, 0, szBuf, MAX_PATH);
		CloseHandle(h);
		if(xx){
			lstrcat(szBuf, TEXT(".apilog.txt"));
			SetDlgItemText(hDlg, IDC_OUTFILE, szBuf);
		}
	}
	else{//Process select canceled
		//SetDlgItemText(hDlg, IDC_EXENAME, TEXT(""));
		//SetDlgItemText(hDlg, IDC_STARTDIR, TEXT(""));
		//SetDlgItemText(hDlg, IDC_OUTFILE, TEXT(""));
		//EnableWindow(GetDlgItem(hDlg, IDC_RUN), FALSE);
	}
}


void OpenLog(HWND hDlg){
	GetDlgItemText(hDlg, IDC_OUTFILE, szLOG, MAX_PATH);
	WIN32_FIND_DATA fd={0};
	HANDLE fh = FindFirstFile(szLOG, &fd);
	if(fh==INVALID_HANDLE_VALUE){
		MessageBox(hDlg, TEXT("Can't open log file. File not exist?"), szLOG, MB_ICONERROR|MB_TOPMOST);
	}
	else{
		FindClose(fh);
		HMODULE hSHELL32 = LoadLibraryA("shell32.dll");
		PFN_ShellExecute pShellExec = (PFN_ShellExecute)(GetProcAddress( hSHELL32, "ShellExecuteW" ) );
		pShellExec(0, 0, szLOG, 0, 0, SW_SHOWMAXIMIZED);
	}
}

void EditDB(HWND hDlg){
	TCHAR	szBuf[MAX_PATH];

	GetDlgItemText(hDlg, IDC_DB, szBuf, MAX_PATH);
	WIN32_FIND_DATA fd={0};
	HANDLE fh = FindFirstFile(szBuf, &fd);
	if(fh==INVALID_HANDLE_VALUE){
		MessageBox(hDlg, TEXT("Can't open database file"), szBuf, MB_ICONERROR|MB_TOPMOST);
	}
	else{
		FindClose(fh);

		HMODULE hSHELL32 = LoadLibraryA("shell32.dll");
		PFN_ShellExecute pShellExec = (PFN_ShellExecute)(GetProcAddress( hSHELL32, "ShellExecuteW" ) );
		pShellExec(0, 0, szBuf, 0, 0, SW_SHOWMAXIMIZED);
	}
}


void SelOutFile(HWND hDlg){
	TCHAR	szExe[MAX_PATH];
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner = hDlg;
	ofn.hInstance=(HINSTANCE)GetModuleHandle(0);
	ofn.lpstrFilter=TEXT("TXT Files\0*.txt\0All Files\0*.*\0\0");
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFile = szExe;
	ofn.lpstrFile[0]='\0';

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if(GetSaveFileName(&ofn)){
		SetDlgItemText(hDlg, IDC_OUTFILE, szExe);
	}
}

void SelDbFile(HWND hDlg){
	TCHAR	szExe[MAX_PATH];
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner = hDlg;
	ofn.hInstance=(HINSTANCE)GetModuleHandle(0);
	ofn.lpstrFilter=TEXT("TXT Files\0*.txt\0All Files\0*.*\0\0");
	ofn.nMaxFile=MAX_PATH;
	ofn.lpstrFile = szExe;
	ofn.lpstrFile[0]='\0';

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if(GetOpenFileName(&ofn)){
		SetDlgItemText(hDlg, IDC_DB, szExe);
	}
}


void DropFile(HWND hDlg, WPARAM wParam){
	TCHAR	szExe[MAX_PATH];
	TCHAR	szBuf2[MAX_PATH];

	DragQueryFile((HDROP)wParam, 0, szExe, MAX_PATH-1);
	SetDlgItemText(hDlg, IDC_EXENAME, szExe);
	SetOutFile(hDlg, szExe);
	InjType=0;
	dwPid=-1;
	EnableWindow(GetDlgItem(hDlg, IDC_RUN), TRUE);
	SetDlgItemText(hDlg, IDC_RUN, TEXT("Run"));

	lstrcpy(szBuf2, szExe);
	for(DWORD i=(DWORD)lstrlen(szBuf2); i>0; i--){if(szBuf2[i-1]==TEXT('\\')){szBuf2[i]=0; break;}}
	SetDlgItemText(hDlg, IDC_STARTDIR, szBuf2);

	EnableWindow(GetDlgItem(hDlg, IDC_ARGS), TRUE);
	EnableWindow(GetDlgItem(hDlg, IDC_STARTDIR), TRUE);
}


void SettingsInit(HWND hDlg){
	TCHAR szBuf[2048];
	TCHAR szBuf2[2048];
	DWORD x;

	CreateToolTip(IDC_COMBO1, hDlg, TEXT("Change this if target crashed"));
	CreateToolTip(IDC_CHECK5, hDlg, TEXT("Don't create log file (if plugin create)"));
	CreateToolTip(IDC_CHECK4, hDlg, TEXT("Include to log only EXE function calls"));
	CreateToolTip(IDC_CHECK2, hDlg, TEXT("Include to log only first function in functions tree"));
	CreateToolTip(IDC_CHECK1, hDlg, TEXT("Include to log thread ID"));
	CreateToolTip(IDC_CHECK3, hDlg, TEXT("Log \"user32.MessageBoxA\" instead \"MessageBoxA\""));
	CreateToolTip(IDC_EDIT2, hDlg,  TEXT("Minimal string length to recognize"));
	CreateToolTip(IDC_EDIT1, hDlg,  TEXT("Maximum string length to output to log"));
	CreateToolTip(IDC_CHECK6, hDlg, TEXT("Enable function profiling in [microseconds] [tics]"));
	CreateToolTip(IDC_CHECK7, hDlg, TEXT("Insert time to log"));
	GetIniPath(szBuf, MAX_PATH);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("Mode"), 0, szBuf);
	SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)TEXT("Normal"));
	SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)TEXT("Safe"));
	SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)TEXT("TLS_NoWaitExe"));
	SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)TEXT("TLS_WaitExe"));
	SendMessage(GetDlgItem(hDlg, IDC_COMBO1), CB_SETCURSEL, x , 0);
	

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("MinStrLen"), 0, szBuf);
	SetDlgItemInt(hDlg, IDC_EDIT2, x, 0);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("MaxStrLen"), 0, szBuf);
	SetDlgItemInt(hDlg, IDC_EDIT1, x, 0);

	//		x = GetPrivateProfileInt(TEXT("Settings"), TEXT("PluginHooks"), 0, szBuf);
	//		SetDlgItemInt(hDlg, IDC_EDIT3, x, 0);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("DisableLog"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK5, BM_CLICK ,0 ,0);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("TID"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK1, BM_CLICK ,0 ,0);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("RootFunc"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK2, BM_CLICK ,0 ,0);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("ExtFuncNames"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK3, BM_CLICK ,0 ,0);

	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("OnlyExeCalls"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK4, BM_CLICK ,0 ,0);

	//Profiler
	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("Profiler"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK6, BM_CLICK ,0 ,0);

	//Time
	x = GetPrivateProfileInt(TEXT("Settings"), TEXT("Time"), 0, szBuf);
	if(x)
		SendDlgItemMessage(hDlg, IDC_CHECK7, BM_CLICK ,0 ,0);


	GetPrivateProfileString(TEXT("Settings"), TEXT("ExcludeModules"), TEXT(""), szBuf2, 2048, szBuf);
	SetDlgItemText(hDlg, IDC_EDIT5, szBuf2);

	GetPrivateProfileString(TEXT("Settings"), TEXT("IncludeModules"), TEXT(""), szBuf2, 2048, szBuf);
	SetDlgItemText(hDlg, IDC_EDIT4, szBuf2);

	CreateToolTip(IDC_EDIT4, hDlg, TEXT("Comma separated INCLUDED DLLs list.   Ex. kernel32.dll, user32.dll, gdi32.dll"));
	CreateToolTip(IDC_EDIT5, hDlg, TEXT("Comma separated EXCLUDED DLLs list.   Ex. kernel32.dll, user32.dll, gdi32.dll"));

	HICON hIco = LoadIcon(GetModuleHandle(0), (LPCWSTR)IDI_ICON1);
	PostMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIco );
}


void SettingsOk(HWND hDlg, WPARAM wParam){
	TCHAR szBuf[2048];
	TCHAR szBuf2[2048];

	//Check include/exclude conflict here
	GetDlgItemText(hDlg, IDC_EDIT4, szBuf, 2048);
	GetDlgItemText(hDlg, IDC_EDIT5, szBuf2, 2048);
	DWORD xmin = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
	DWORD xmax = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
	if(szBuf[0] && szBuf2[0]){
		MessageBox(hDlg, TEXT("Include/Exclude List Conflict. Disable one of them"), 0, MB_TOPMOST|MB_ICONERROR);
	}
	else if(xmin >= xmax){
		MessageBox(hDlg, TEXT("Invalid string range"), 0, MB_TOPMOST|MB_ICONERROR);
	}
	else{
		SaveSettings(hDlg);
		EndDialog(hDlg, LOWORD(wParam));
	}
}
