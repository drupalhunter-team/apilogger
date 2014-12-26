
#include "stdafx.h"
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
#include "about.h"

//#pragma comment(linker,"/MERGE:.rdata=.text")
//#pragma comment(linker,"/ENTRY:New_WinMain")

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shlwapi.lib")

DWORD	dwPid=-1;	//Attach Process PID
DWORD	InjType=0;	//0-create new, 1-attach


LRESULT CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){	
	switch (message)
	{
	case WM_INITDIALOG:
		MainInit(hDlg);
		break;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDCANCEL){
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		else if(LOWORD(wParam)==IDC_OPTIONS){
			MainOptions(hDlg);
		}
		else if(LOWORD(wParam)==ID_SEL_EXE){
			MainSelectExe(hDlg);
		}
		else if(LOWORD(wParam)==IDC_RUN){//INJECTING!
			InjRun(hDlg);
		}
		else if(LOWORD(wParam)==ID_ATTACH){//Attach button selected
			Attach(hDlg);
		}
		else if(LOWORD(wParam)==ID_OPENLOG){
			OpenLog(hDlg);
		}
		else if(LOWORD(wParam)==IDC_EDITDB){//Open DB File
			EditDB(hDlg);
		}
		else if(LOWORD(wParam)==ID_SELOUT){
			SelOutFile(hDlg);
		}
		else if(LOWORD(wParam)==ID_SELDB){
			SelDbFile(hDlg);
		}
		else if(LOWORD(wParam) == IDC_ABOUT){
			DialogBox( GetModuleHandle(0), (LPCTSTR)IDD_ABOUT, hDlg, (DLGPROC)AboutDlgProc);
/*
			MessageBox(hDlg, TEXT("\
Win32 processes API spy\n\n\
(c)2004-2011 black_ninja\n\
mail: black_ninja2000@mail.ru\n\
icq:  404558476\
"), 
TEXT("API Logger"), 
MB_OK|MB_TOPMOST|MB_ICONINFORMATION);
*/
			return TRUE;
		}
		break;
	case WM_DROPFILES:
		DropFile(hDlg, wParam);
		break;
	}
	return FALSE;
}

void cmd_line_inj(LPWSTR sz_targ, LPWSTR sz_args){
	TCHAR	szDLL[MAX_PATH]={0};
	TCHAR	szDir[MAX_PATH]={0};

	GetModuleFileName(0, szDLL, MAX_PATH);
	for(DWORD i=(DWORD)lstrlen(szDLL); i>0; i--){if(szDLL[i-1]==TEXT('\\')){szDLL[i]=0; break;}}

	lstrcat(szDLL, TEXT("intruder.dll"));
	KInject inj;
	if(inj.CreateAndInject2Process(sz_targ, sz_args, szDLL, szDir)==-1){
		MessageBox(0, TEXT("Inject Error"), 0, MB_ICONERROR|MB_OK);
	}
}

/*
Usage:
injector.exe			- User Interface
injector.exe exe		- Start Process With Inject
injector.exe exe args	- Start Process With Args And Inject
*/
//void New_WinMain(){
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	int args;
	LPWSTR* argv=CommandLineToArgvW(GetCommandLineW(), &args);

	if(args == 1){
		InitCommonControls();
		DialogBox((HINSTANCE)GetModuleHandle(0), (LPCTSTR)IDD_DIALOG1, 0, (DLGPROC)MainDlgProc);
	}
	else if(args == 2){	//targ
		cmd_line_inj(argv[1], 0);
	}
	else if(args > 2){	//targ, args
		cmd_line_inj(argv[1], argv[2]);
	}
	else{
		MessageBox(0, TEXT("Invalid command line"), 0, MB_ICONERROR|MB_OK);
	}
	ExitProcess(0);
}


void GetIniPath(TCHAR* buf, DWORD len){
	GetModuleFileName((HMODULE)0, buf, len-1);
	for(DWORD i=(DWORD)lstrlen(buf); i>0; i--){if(buf[i-1]=='\\'){buf[i]=0; break;}}
	lstrcat(buf, TEXT("settings.ini"));
}

void SetOutFile(HWND hDlg, TCHAR* szEXEFile){
	TCHAR szBuf[MAX_PATH];

	lstrcpy(szBuf, szEXEFile);
	lstrcat(szBuf, TEXT(".apilog.txt"));

	SetDlgItemText(hDlg, IDC_OUTFILE, szBuf);
}

void SavePath(HWND hDlg){
	TCHAR szBuf[MAX_PATH];
	TCHAR szIni[MAX_PATH];
	GetIniPath(szIni, MAX_PATH);

	GetDlgItemText(hDlg, IDC_DB, szBuf, MAX_PATH);
	WritePrivateProfileString(TEXT("Settings"), TEXT("DBFile"), szBuf, szIni);

	GetDlgItemText(hDlg, IDC_OUTFILE, szBuf, MAX_PATH);
	WritePrivateProfileString(TEXT("Settings"), TEXT("OutLogFile"), szBuf, szIni);

	GetDlgItemText(hDlg, IDC_EXENAME, szBuf, MAX_PATH);
	WritePrivateProfileString(TEXT("Settings"), TEXT("Target"), szBuf, szIni);


	GetDlgItemText(hDlg, IDC_ARGS, szBuf, MAX_PATH);
	WritePrivateProfileString(TEXT("Settings"), TEXT("Args"), szBuf, szIni);

	GetDlgItemText(hDlg, IDC_STARTDIR, szBuf, MAX_PATH);
	WritePrivateProfileString(TEXT("Settings"), TEXT("WorkDir"), szBuf, szIni);

}



LRESULT CALLBACK DlgSettings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SettingsInit(hDlg);
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		else if (LOWORD(wParam) == IDOK) {
			SettingsOk(hDlg, wParam);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

void WritePrivateProfileInt(TCHAR* szSec, TCHAR* szKey, DWORD v, TCHAR* szFile){
	TCHAR szBuf[16];

	wsprintf(szBuf,  TEXT("%d"), v);
	WritePrivateProfileString(szSec, szKey, szBuf, szFile);
}

DWORD IsChecked(HWND hDlg, int id){
	DWORD Flag = 0;
	if(IsDlgButtonChecked(hDlg, id) == BST_CHECKED){
		Flag = 1;
	}
	else{
		Flag = 0;
	}
	return Flag;
}

void SaveSettings(HWND hDlg){
	TCHAR szBuf[2048];
	TCHAR szIni[MAX_PATH];
	DWORD x;
	GetIniPath(szIni, MAX_PATH);

	GetDlgItemText(hDlg, IDC_EDIT4, szBuf, 2048);
	WritePrivateProfileString(TEXT("Settings"), TEXT("IncludeModules"), szBuf, szIni);

	GetDlgItemText(hDlg, IDC_EDIT5, szBuf, 2048);
	WritePrivateProfileString(TEXT("Settings"), TEXT("ExcludeModules"), szBuf, szIni);

	x = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("MinStrLen"), x, szIni);

	x = GetDlgItemInt(hDlg, IDC_EDIT1, 0, 0);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("MaxStrLen"), x, szIni);

//	x = GetDlgItemInt(hDlg, IDC_EDIT3, 0, 0);
//	WritePrivateProfileInt(TEXT("Settings"), TEXT("PluginHooks"), x, szIni);

	x = ((int)SendMessage(GetDlgItem(hDlg, IDC_COMBO1) , CB_GETCURSEL , 0 , 0));
	WritePrivateProfileInt(TEXT("Settings"), TEXT("Mode"), x, szIni);

	WritePrivateProfileInt(TEXT("Settings"), TEXT("DisableLog"),   IsChecked(hDlg, IDC_CHECK5), szIni);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("TID"),          IsChecked(hDlg, IDC_CHECK1), szIni);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("RootFunc"),     IsChecked(hDlg, IDC_CHECK2), szIni);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("ExtFuncNames"), IsChecked(hDlg, IDC_CHECK3), szIni);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("OnlyExeCalls"), IsChecked(hDlg, IDC_CHECK4), szIni);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("Profiler"),     IsChecked(hDlg, IDC_CHECK6), szIni);
	WritePrivateProfileInt(TEXT("Settings"), TEXT("Time"),         IsChecked(hDlg, IDC_CHECK7), szIni);
}
