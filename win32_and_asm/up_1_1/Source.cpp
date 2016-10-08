#undef UNICODE
#include <windows.h>
#include "resource.h"
#include <cstring>
extern "C" int __fastcall aF(char*, int*);
INT_PTR CALLBACK DlgProc(HWND hWin, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	static OPENFILENAME ofn;       // common dialog box structure
	static char szFile[260];       // buffer for file name
	static HWND hwnd;              // owner window
	static HWND hwndList;
	static char *pch;
	static char *pchend;
	static char  str[100] = { 0 };
	static int n=0;
	static int k = 0;
	static int begins[100];
	switch (msg)
	{
	case WM_INITDIALOG:

		hwndList = GetDlgItem(hWin, IDC_LIST2);
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFile = szFile;
		// Set lpstrFile[0] to '\0' so that GetOpenFileName does not
		// use the contents of szFile to initialize itself.
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hWin, LOWORD(wParam));
			return TRUE;
			break;
		case IDCANCEL:
			EndDialog(hWin, LOWORD(wParam));
			return TRUE;
			break;
		case IDC_BUTTON1:
			if (GetOpenFileName(&ofn) == TRUE)
			{
				//c++ start
				SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)ofn.lpstrFile);
				char *str = strtok(ofn.lpstrFile, "\:.");
				while (str != NULL)
				{
					SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)str);
					str = strtok(NULL, "\\:.");
				}
				//c++ end
				//asm start
				/*SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)ofn.lpstrFile);
				n = aF(ofn.lpstrFile, begins);
				for (int i = 0; i < n - 1; i++)
				{
					k = 0;
					memset(str, 0, 100);
					if (begins[i + 1] - begins[i] > 1)
					{
						pch = &ofn.lpstrFile[begins[i]];
						pchend = &ofn.lpstrFile[begins[i + 1]];
						for (int j = begins[i]; j < begins[i + 1]-1; j++)
						{
							str[k++] = ofn.lpstrFile[j];
						}
						SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)str);
					}
				}
				pch = &ofn.lpstrFile[begins[n - 1]];
				SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pch);
				//asm end*/
			}
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWin, LOWORD(wParam));
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	switch (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc))
	{
	case IDOK:
		MessageBox(NULL, "OK", "Button", MB_ICONASTERISK);
		break;
	case IDCANCEL:
		MessageBox(NULL, "Cancel", "Button", MB_ICONASTERISK);
		break;
	}
}