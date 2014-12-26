#pragma once

BOOL CreateToolTip(int toolID, HWND hDlg, TCHAR* pText);
void MainInit(HWND hDlg);
void MainOptions(HWND hDlg);
void MainSelectExe(HWND hDlg);
void InjRun(HWND hDlg);
void Attach(HWND hDlg);
void OpenLog(HWND hDlg);
void EditDB(HWND hDlg);
void SelOutFile(HWND hDlg);
void SelDbFile(HWND hDlg);
void DropFile(HWND hDlg, WPARAM wParam);


void SettingsInit(HWND hDlg);
void SettingsOk(HWND hDlg, WPARAM wParam);
