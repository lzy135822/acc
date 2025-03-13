#pragma once
#include<Windows.h>
#include<stdio.h>
HHOOK g_hook = NULL;
extern "C" _declspec(dllexport) BOOL InstallHook();
extern "C" _declspec(dllexport) BOOL UnInstallHook();
LRESULT CALLBACK KeyBoard(int ncode, WPARAM wParam, LPARAM lParam);