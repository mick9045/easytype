#pragma once
#include "stdafx.h"
#include "BaseDialogWindow.h"
#include "UserManagement.h"
#include "KeyboardDialog.h"
#include "TextDialog.h"
#include "BaseTypingLanguage.h"
#include "GameStatisticsDialog.h"

namespace CourseWork_WinApi
{
	class MainDialog :
		public BaseDialogWindow
	{
	public:
		MainDialog();
		~MainDialog();
		INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		VOID Cls_OnMove(HWND hwnd, INT x, INT y);
		VOID Cls_OnSize(HWND hwnd, UINT state, INT cx, INT cy);
		VOID Cls_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo);
		VOID Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, INT cRepeat, UINT flags);
		VOID Cls_OnChar(HWND hwnd, TCHAR ch, INT cRepeat);
		HBRUSH Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, INT type);
		VOID Cls_OnCommand(HWND hwnd, INT id, HWND hwndCtl, UINT codeNotify);
		VOID Cls_OnDestroy(HWND hwnd);
		VOID Cls_OnClose(HWND hwnd);
		VOID Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu);
		VOID Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, INT item, HMENU hmenuPopup, UINT flags);
		VOID Cls_OnTimer(HWND hwnd, UINT id);
		/**/
		VOID OnOpenFile();
		VOID UpdateMenu();
		VOID AlignElements();
	private:
		/**/
		VOID UpdateSpeedStat();
		BOOL CheckIfLevel(INT id);
		VOID OnLevelEnd();
		/**/
		UserManagement _userManagement;
		BaseTypingLanguage * _typingLanguage;
		KeyboardDialog _keyboard;
		TextDialog _text;
		GameStatisticsDialog _statistics;
		INT _iCurrentLevel;
		DWORD _millisecondsStart;

		/**/
		HMENU _hmKeyboardLanguage;
		HMENU _hmUILanguage;
		HMENU _hmLevel;
		HMENU _hmRuLevel;
		HMENU _hmEnLevel;
	};

}

