#pragma once
#include <windows.h>
#include <CommCtrl.h>
#include "DPI_Scale.h"
#include "resource.h"
#include "LocalizationObject.h"

namespace CourseWork_WinApi
{
	class BaseDialogWindow
	{
	public:
		virtual  ~BaseDialogWindow();
		BaseDialogWindow(INT nResource);
		BOOL IsCreated();
		HWND Create(HWND hwndParent = NULL, HINSTANCE hInstance = GetModuleHandle(NULL));
		INT_PTR CreateModal(HWND hwndParent = NULL, HINSTANCE hInstance = GetModuleHandle(NULL));
		HWND GetWindowHandle();
		INT GetResourceID();
		HWND hWindow();
		SIZE GetClientSize();
		SIZE GetSize();
		RECT GetRect();
		POINT GetLocalPosition();
		static tString GetText(HWND hWnd);
		static POINT GetLocalPosition(HWND hWnd);
		static SIZE GetClientSize(HWND hWnd);
		static SIZE GetSize(HWND hWnd);
		static INT GetMenuItemPosById(HMENU hMenu, INT id);
		/*~~~~~~~~~~~~~~ methods~~~~~~~~~~~~~~~~~~*/
		void Close();
	protected:
		HWND _hwnd;
		INT _nResource;
		INT _nResult;
		static DPI_Scale _dpiScale;
		static LocalizationObject _local;
		/*~~~~~~~~~~~~~~ methods~~~~~~~~~~~~~~~~~~*/
		BOOL isModal();
		inline static BaseDialogWindow * GetWindowObjectFromHandle(HWND hWnd);
		virtual INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	private:
		BOOL _bModal;

		//prohobit coping
		BaseDialogWindow(const BaseDialogWindow &);
		static INT_PTR CALLBACK MessageRoute(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // routes messages from all windows
	};

}