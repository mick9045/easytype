#pragma once
#include "BaseDialogWindow.h"
#include "UserManagement.h"
#include "stdafx.h"


namespace CourseWork_WinApi
{
	class UserLogInDialog :
		public BaseDialogWindow
	{
	public:
		UserLogInDialog(UserManagement & managment);
		~UserLogInDialog();
		INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	protected:
		tString _nickName;
		tString _password;
		/**/
	private:
		/*event handlers*/
		VOID Cls_OnClose(HWND hwnd);
		VOID Cls_OnDestroy(HWND hwnd);
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		VOID Cls_OnCommand(HWND hwnd, INT id, HWND hwndCtl, UINT codeNotify);
		VOID Cls_OnDrawItem(HWND hwnd, CONST DRAWITEMSTRUCT * lpDrawItem);
		/*``````````````````````````````````````````````````````````````*/
		VOID OnLogInButtonClick(HWND hCtl);
		VOID OnRegisterButtonClick(HWND hCtl);
		VOID OnNickNameEditChange(HWND hCtl);
		VOID OnPasswordEditChange(HWND hCtl);
		/**/
		VOID InitUIText();
		VOID OnChangeLanguageButtonClick(INT buttonId);
		/**/
		UserManagement & _userManagement;
		/**/
		size_t _iMinNameLength;
		size_t _iMaxNameLength;
		size_t _iMinPasswordLength;
		size_t _iMaxPasswordLength;

		HFONT _hFont;
	};
}
