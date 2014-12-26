#pragma once

LRESULT CALLBACK ProcessDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL lvOnInitDialog(HWND, WPARAM, LPARAM);
BOOL OnNotify(HWND, WPARAM, LPARAM);
void FillList(HWND hDlg);
