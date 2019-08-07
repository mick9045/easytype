#include "stdafx.h"
#include "resource.h"
#include "MainDialog.h"
#include "UserLogInDialog.h"
#include <CommCtrl.h>
#include <gdiplus.h>


#pragma comment(lib, "comctl32")
#pragma comment (lib,"Gdiplus.lib")


void inline EnableCommonControls();

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, INT nCmdShow)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	EnableCommonControls();
	auto mainDialog = new CourseWork_WinApi::MainDialog();
	HWND hMainWindow = mainDialog->Create();
	MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		/*
		if (!IsDialogMessage(hMainWindow, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		*/
		GdiplusShutdown(gdiplusToken);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	delete mainDialog;
	return NULL;
}

void inline EnableCommonControls()
{
	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
	InitCommonControlsEx(&icc);
	LoadLibrary(TEXT("RICHED20.DLL"));
	
}

