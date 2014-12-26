
#include "stdafx.h"

#include <windows.h>
#include <commctrl.h>
#include <psapi.h>
#include "proclist.h"
#include "resource.h"
#include "kinject.h"
#include "injector.h"

#pragma comment(lib,"psapi.lib")

extern DWORD dwPid;
static int nRow=-1;

DWORD String2Dword(TCHAR *str){
	DWORD Result=0;
	int idx=0;
	DWORD tRes;
	TCHAR Zero[]=TEXT("0");

	for(int i=lstrlen(str); i>0; i--){
		BYTE digit=(BYTE)(str[idx]-Zero[0]);
		tRes=digit;
		for(int j=0; j<i-1; j++){
			tRes*=10;
		}
		idx++;
		Result+=tRes;
	}
	return Result;
}

LRESULT CALLBACK ProcessDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{
	case WM_INITDIALOG:
		EnableDebugPriv();
		lvOnInitDialog(hDlg,wParam,lParam);
		SetFocus(GetDlgItem(hDlg, IDC_LIST1));
		break;
	case WM_COMMAND:
		if((LOWORD(wParam)==IDCANCEL)){
			dwPid=-1;

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		else if((LOWORD(wParam)==IDOK)){
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		else if((LOWORD(wParam)==IDC_REFRESH)){
			ListView_DeleteAllItems(GetDlgItem(hDlg, IDC_LIST1));
			FillList(hDlg);
			SetFocus(GetDlgItem(hDlg, IDC_LIST1));
			return TRUE;
		}
	case WM_NOTIFY:
		return OnNotify(hDlg, wParam, lParam);
	}
	return FALSE;
}

void lvAddColumn(HWND m_hWnd,int col, int width, const TCHAR *title, BOOL left)
{
    LV_COLUMN c;

    c.mask     = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
    c.fmt      = left ? LVCFMT_LEFT : LVCFMT_RIGHT;
    c.cx       = width;
    c.pszText  = (TCHAR *) title;
    c.iSubItem = col;
                    
    ListView_InsertColumn(m_hWnd, col, &c);
}



    
void lvAddItem(HWND m_hWnd,int col, const TCHAR *text, int iImage)
{
    LV_ITEM item;

    if (iImage>=0)
        item.mask = LVIF_TEXT | LVIF_IMAGE;
    else
        item.mask = LVIF_TEXT;

    // if column is 0, adding a row
    if (col==0)
        nRow ++;

    item.pszText  = (TCHAR *) text;
    item.iItem    = nRow;
    item.iSubItem = col;
    item.iImage   = iImage;
        
    if (col==0)
        ListView_InsertItem(m_hWnd, &item);
    else
        ListView_SetItem(m_hWnd, &item);
}

void lvAddItem(HWND m_hWnd,int col, int value, int iImage)
{
	TCHAR temp[32];

	wsprintf(temp, TEXT("%d"), value);

	lvAddItem(m_hWnd,col, temp, iImage);
}
BOOL lvOnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	HWND m_hWnd = GetDlgItem(hWnd, IDC_LIST1);
	ListView_SetExtendedListViewStyleEx(m_hWnd,0,LVS_EX_GRIDLINES);     

	lvAddColumn(m_hWnd,0, 100,	TEXT("Process"),1);
	lvAddColumn(m_hWnd,1, 50,	TEXT("PID"),1);
	lvAddColumn(m_hWnd,2, 300,	TEXT("Path"),1);

	FillList(hWnd);
	return true;
}

BOOL OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam){

	TCHAR rslt[256];
	LPNMHDR  lpnmh=(LPNMHDR)lParam;//corresponds to listview window
	LPNMITEMACTIVATE lp = (LPNMITEMACTIVATE) lParam;

	switch(lpnmh->code){
	case LVN_ITEMACTIVATE:return true;
	case NM_DBLCLK:
		if(lp->iItem!=-1){
			ListView_GetItemText(lp->hdr.hwndFrom, lp->iItem, 1, rslt, 256);
			dwPid=String2Dword(rslt);
			EndDialog(hWnd, LOWORD(wParam));
		}
		return true;
	case NM_CLICK:
		if(lp->iItem!=-1){
			ListView_GetItemText(lp->hdr.hwndFrom, lp->iItem, 1, rslt, 256);
			dwPid=String2Dword(rslt);
		}
		return true;
	}
	return FALSE;
}

void FillList(HWND hWnd){
	DWORD	pids[1024];
	DWORD	cbNeeded;
	TCHAR	szModuleName[MAX_PATH];
	HANDLE	ProcessHandle;
	TCHAR	buffer[32];
	
	HMODULE hPSAPI = LoadLibraryA("psapi.dll");

	PFN_OpenProcess pOpenProcess = (PFN_OpenProcess)(GetProcAddress( GetModuleHandleA("kernel32.dll"), "OpenProcess" ) );
	PFN_EnumProcesses pEnumProc = (PFN_EnumProcesses)(GetProcAddress( hPSAPI, "EnumProcesses" ) );
	PFN_GetModuleBaseName pGetModuleBaseName = (PFN_GetModuleBaseName)(GetProcAddress( hPSAPI, "GetModuleBaseNameW" ) );
	PFN_GetModuleFileNameEx pGetModuleFileNameEx = (PFN_GetModuleFileNameEx)(GetProcAddress( hPSAPI, "GetModuleFileNameExW" ) );

	HWND m_hWnd = GetDlgItem(hWnd, IDC_LIST1);
	nRow=-1;
	if(pEnumProc(pids, 4096, &cbNeeded)){
		SetDlgItemInt(hWnd, IDC_PROCESSES, cbNeeded/4, FALSE);

		for(DWORD i=0; i<cbNeeded/4; i++){
			ProcessHandle = pOpenProcess(PROCESS_ALL_ACCESS, NULL, pids[i]);
			if(ProcessHandle){
				if(	pGetModuleBaseName(ProcessHandle, 0, szModuleName, MAX_PATH)){
					lvAddItem(m_hWnd,0, szModuleName,-1);

					wsprintf(buffer, TEXT("%lu"), (int)pids[i]);	
					lvAddItem(m_hWnd,1, buffer, -1);

					pGetModuleFileNameEx(ProcessHandle, 0, szModuleName,MAX_PATH);
					lvAddItem(m_hWnd,2, szModuleName,-1);
				}
				CloseHandle(ProcessHandle);
			}
		}
	}
}
