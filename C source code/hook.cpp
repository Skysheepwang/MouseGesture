#include "hook.h"


LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	MOUSEHOOKSTRUCT* p = (MOUSEHOOKSTRUCT*)lParam;
	const wchar_t *info = NULL;
	wchar_t text[50], data[20];

	PAINTSTRUCT ps;
	HDC hdc;

	if (nCode >= 0)
	{
		if (wParam == WM_LBUTTONDOWN)      info = L"鼠标左键按下";
		else if (wParam == WM_LBUTTONUP)        info = L"鼠标左键抬起";
		else if (wParam == WM_RBUTTONDOWN)   info = L"鼠标右键按下";
		else if (wParam == WM_RBUTTONUP)     info = L"鼠标右键抬起";

		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));
		wsprintf(text, L"%s", info);
		wsprintf(data, L"位置：x=%d,y=%d", p->pt.x, p->pt.y);

		hdc = GetDC(hgWnd);
		InvalidateRect(hgWnd,NULL,true);
		UpdateWindow(hgWnd);
		TextOut(hdc, 10, 10, text, wcslen(text));
		TextOut(hdc, 10, 30, data, wcslen(data));
		ReleaseDC(hgWnd, hdc);
	}

	return CallNextHookEx(key_hook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const wchar_t *info = NULL;
	wchar_t text[50], data[20];

	PAINTSTRUCT ps;
	HDC hdc;

	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)      info = L"普通按鍵抬起";
		else if (wParam == WM_KEYUP)        info = L"普通按鍵按下";
		else if (wParam == WM_SYSKEYDOWN)   info = L"系統按鍵抬起";
		else if (wParam == WM_SYSKEYUP)     info = L"系統按鍵按下";

		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));
		wsprintf(text, L"%s - 键盘码 [%04d], 扫描码 [%04d]  ", info, p->vkCode, p->scanCode);
		wsprintf(data, L"按键码目测为： %c  ", p->vkCode);

		hdc = GetDC(hgWnd);
		TextOut(hdc, 10, 50, text, wcslen(text));
		TextOut(hdc, 10, 70, data, wcslen(data));
		ReleaseDC(hgWnd, hdc);
	}

	return CallNextHookEx(key_hook, nCode, wParam, lParam);
}