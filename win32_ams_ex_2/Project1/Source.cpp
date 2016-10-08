#include <windows.h>
#include "resource.h"
extern "C" void __stdcall toHex(int, char*);
INT_PTR CALLBACK DlgProc(HWND hWin, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int n;
	switch (msg)
	{
	case WM_CLOSE:
		EndDialog(hWin, 0);
		break;
	default:
		return FALSE;
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
		case IDD_BUTTON1:
		{
			n = GetDlgItemInt(hWin, IDC_EDIT1, nullptr, FALSE);
			char* o = new char[9];
			toHex(n, o);
			char k = o[0];
			n = 0;
			while (k == '0')
			{
				n++;
				k = o[n];
			}
			int t = 9 - n;
			char *p = new char[t];
			for (int i = 0; i < t; i++)
				p[i] = o[n + i];
			SetDlgItemText(hWin, IDC_EDIT2, p);
		}
		break;
		}
		break;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

