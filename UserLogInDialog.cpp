#include "stdafx.h"
#include "UserLogInDialog.h"
#include "resource.h"
#include <strsafe.h>

namespace CourseWork_WinApi
{

	INT_PTR UserLogInDialog::DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
			HANDLE_MSG(hwnd, WM_DESTROY, Cls_OnDestroy);
			HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
			HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
			HANDLE_MSG(hwnd, WM_DRAWITEM, Cls_OnDrawItem);
		}
		return false;
	}

	UserLogInDialog::UserLogInDialog(UserManagement & managment)
		:BaseDialogWindow(IDD_DIALOG_LOG_IN),
		_userManagement(managment)
	{
		_iMinNameLength = 2;
		_iMaxNameLength = 24;
		_iMinPasswordLength = 4;
		_iMaxPasswordLength = 16;

	}


	UserLogInDialog::~UserLogInDialog()
	{
		DeleteObject(_hFont);
	}

	

	VOID UserLogInDialog::Cls_OnClose(HWND hwnd)
	{
		Close();
	}

	void UserLogInDialog::Cls_OnDestroy(HWND hwnd)
	{

	}

	BOOL UserLogInDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		HBITMAP hbmpRuFlag = ::LoadBitmap(
			::GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDB_BITMAP_FLAG_RU)
		);

		HBITMAP hbmpEnFlag = ::LoadBitmap(
			::GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDB_BITMAP_FLAG_EN)
		);

		::SendDlgItemMessage(
			hwnd, IDC_BUTTON_LANGUAGE_EN, BM_SETIMAGE, IMAGE_BITMAP,
			reinterpret_cast<LPARAM>(hbmpEnFlag)
		);
		::SendDlgItemMessage(
			hwnd, IDC_BUTTON_LANGUAGE_RU, BM_SETIMAGE, IMAGE_BITMAP,
			reinterpret_cast<LPARAM>(hbmpRuFlag)
		);

		/*Setting font*/
		LOGFONT LogFont;
		::ZeroMemory(&LogFont, sizeof(LOGFONT));
		LogFont.lfHeight = _dpiScale.Scale(45);
		::StringCchCopy(LogFont.lfFaceName, 32, TEXT("Times New Roman"));
		LogFont.lfItalic = TRUE;
		_hFont = ::CreateFontIndirect(&LogFont);
		::SendDlgItemMessage(
			hwnd,
			IDC_STATIC_LOG_IN_TITLE,
			WM_SETFONT,
			reinterpret_cast<WPARAM>(_hFont),
			MAKELPARAM(TRUE, NULL)
		);
		
		/**/
		
		_local.SetLanguage(Language::Russian);

		InitUIText();
		

		
		return TRUE;
	}

	void UserLogInDialog::Cls_OnCommand(HWND hwnd, INT id, HWND hwndCtl, UINT codeNotify)
	{
		switch (GetDlgCtrlID(hwndCtl))
		{
		case IDC_BUTTON_LOG_IN:
			switch (codeNotify)
			{
			case BN_CLICKED:
				OnLogInButtonClick(hwndCtl);
				break;
			}
			break;
		case IDC_BUTTON_REGISTER:
			switch (codeNotify)
			{
			case BN_CLICKED:
				OnRegisterButtonClick(hwndCtl);
				break;
			}
			break;
		case IDC_BUTTON_LANGUAGE_EN:
			OnChangeLanguageButtonClick(IDC_BUTTON_LANGUAGE_EN);
			break;
		case IDC_BUTTON_LANGUAGE_RU:
			OnChangeLanguageButtonClick(IDC_BUTTON_LANGUAGE_RU);
			break;
		case IDC_EDIT_NAME:
			switch (codeNotify)
			{
			case EN_CHANGE:
				OnNickNameEditChange(hwndCtl);
				break;
			}
			break;
		case IDC_EDIT_PASSWORD:
			switch (codeNotify)
			{
			case EN_CHANGE:
				OnPasswordEditChange(hwndCtl);
				break;
			}
			break;
		}
	}

	void UserLogInDialog::Cls_OnDrawItem(HWND hwnd, CONST DRAWITEMSTRUCT * lpDrawItem)
	{

		switch (lpDrawItem->CtlType)
		{
			//ODT_BUTTON:
		case ODT_BUTTON:
			if (lpDrawItem->itemAction == ODA_DRAWENTIRE)
			{
				if (lpDrawItem->itemState == ODS_FOCUS)
				{
					RECT rect = lpDrawItem->rcItem;
					if (lpDrawItem->itemState & ODS_HOTLIGHT)
						SetBkColor(lpDrawItem->hDC, RGB(255, 0, 0));
					Ellipse(lpDrawItem->hDC, rect.left, rect.top, rect.right, rect.bottom);
					DrawText(lpDrawItem->hDC, TEXT("Log In"), 6, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			else if (lpDrawItem->itemAction == ODA_FOCUS)
			{

				RECT rect = lpDrawItem->rcItem;
				if (lpDrawItem->itemState & ODS_HOTLIGHT)
					SetBkColor(lpDrawItem->hDC, RGB(122, 0, 0));
				Ellipse(lpDrawItem->hDC, rect.left, rect.top, rect.right, rect.bottom);
				DrawText(lpDrawItem->hDC, TEXT("shit"), 6, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			}
			else {
				::MessageBox(NULL, _TEXT("chudo"), NULL, MB_OK);
			}
		}
	}

	VOID UserLogInDialog::OnLogInButtonClick(HWND hCtl)
	{
		HWND hwndEditName = GetDlgItem(_hwnd, IDC_EDIT_NAME);
		HWND hwndEditPassword = GetDlgItem(_hwnd, IDC_EDIT_PASSWORD);
		tString name = GetText(hwndEditName);
		tString password = GetText(hwndEditPassword);

		EDITBALLOONTIP tip;
		tString title = _local.QueryString(IDS_STRING_WARNING);
		tip.cbStruct = sizeof(EDITBALLOONTIP);
		tip.pszText = NULL;
		tip.pszTitle = title.c_str();
		tip.ttiIcon = TTI_WARNING;
		
		if (name.length() == 0 && password.length() == 0)
		{
			MessageBox(
				_hwnd,
				_local.QueryString(IDS_STRING_EMPTY_FIELDS).c_str(),
				title.c_str(),
				MB_OK | MB_ICONWARNING
			);
			return;
		}
		else if (name.length() < _iMinNameLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_SHORT);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditName, &tip);
		}
		else if (name.length() > _iMaxNameLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_LONG);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditName, &tip);
		}
		else if (password.length() < _iMinPasswordLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_SHORT);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditPassword, &tip);
		}
		else if (password.length() > _iMaxPasswordLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_LONG);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditPassword, &tip);
		}
		else if (!_userManagement.IsUserExists(_nickName))
		{
			tString text = _local.QueryString(IDS_STRING_USER_DOES_NOT_EXIST);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditName, &tip);
		}
		else if (_userManagement.IsUserExists(_nickName) &&
			_userManagement.GetUserByNickname(_nickName)->GetPassword() != password)
		{
			tString text = _local.QueryString(IDS_STRING_INVALID_PASSWORD);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditPassword, &tip);
		}
		else
		{
			if (_userManagement.LogIn(name, password) == LoginResult::SUCCESS)
			{
				_nResult = IDOK;
				Close();
			}
			else
			{
				//TODO: insert message box here
			}
		}
	}

	VOID UserLogInDialog::OnRegisterButtonClick(HWND hCtl)
	{
		HWND hwndEditName = GetDlgItem(_hwnd, IDC_EDIT_NAME);
		HWND hwndEditPassword = GetDlgItem(_hwnd, IDC_EDIT_PASSWORD);
		tString name = GetText(hwndEditName);
		tString password = GetText(hwndEditPassword);

		EDITBALLOONTIP tip;
		tString title = _local.QueryString(IDS_STRING_WARNING);
		tip.cbStruct = sizeof(EDITBALLOONTIP);
		tip.pszText = NULL;
		tip.pszTitle = title.c_str();
		tip.ttiIcon = TTI_WARNING;

		if (name.length() == 0 && password.length() == 0)
		{
			MessageBox(
				_hwnd,
				_local.QueryString(IDS_STRING_EMPTY_FIELDS).c_str(),
				title.c_str(),
				MB_OK | MB_ICONWARNING
			);
			return;
		}
		else if (name.length() < _iMinNameLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_SHORT);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditName, &tip);
		}
		else if (name.length() > _iMaxNameLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_LONG);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditName, &tip);
		}
		else if (password.length() < _iMinPasswordLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_SHORT);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditPassword, &tip);
		}
		else if (password.length() > _iMaxPasswordLength)
		{
			tString text = _local.QueryString(IDS_STRING_TOO_LONG);
			tip.pszText = text.c_str();
			Edit_ShowBalloonTip(hwndEditPassword, &tip);
		}
		else
		{
			User * newUser = _userManagement.NewUser(name, password);
			if (newUser != nullptr)
			{
				_userManagement.LogIn(*newUser);
				_nResult = IDOK;
				Close();
			}
			else
			{
				tString text = _local.QueryString(IDS_STRING_USED_NAME);
				tip.pszText = text.c_str();
				Edit_ShowBalloonTip(hwndEditName, &tip);
			}
		}
	}

	VOID UserLogInDialog::OnNickNameEditChange(HWND hCtl)
	{
		_nickName = GetText(hCtl);
	}

	VOID UserLogInDialog::OnPasswordEditChange(HWND hCtl)
	{
		_password = GetText(hCtl);
	}

	VOID UserLogInDialog::OnChangeLanguageButtonClick(INT buttonId)
	{
		switch (buttonId)
		{
		case IDC_BUTTON_LANGUAGE_EN:
			if (_local.GetLanguage() == Language::English)
			{
				break;
			}
			_local.SetLanguage(Language::English);
			InitUIText();
			break;
		case IDC_BUTTON_LANGUAGE_RU:
			if (_local.GetLanguage() == Language::Russian)
			{
				break;
			}
			_local.SetLanguage(Language::Russian);
			InitUIText();
			break;
		default:
			break;
		}
	}

	VOID UserLogInDialog::InitUIText()
	{
		HWND hUserName = GetDlgItem(_hwnd, IDC_EDIT_NAME);
		HWND hPassword = GetDlgItem(_hwnd, IDC_EDIT_PASSWORD);
		HWND hLogInButton = GetDlgItem(_hwnd, IDC_BUTTON_LOG_IN);
		HWND hRegisterButton = GetDlgItem(_hwnd, IDC_BUTTON_REGISTER);
		Edit_SetCueBannerText(hUserName, _local.QueryString(IDS_STRING_USER_NAME).c_str());
		Edit_LimitText(hUserName, 24);
		Edit_SetCueBannerText(hPassword, _local.QueryString(IDS_STRING_PASSWORD).c_str());
		Edit_LimitText(hPassword, 12);
		SetWindowText(hLogInButton, _local.QueryString(IDS_STRING_LOG_IN).c_str());
		SetWindowText(hRegisterButton, _local.QueryString(IDS_STRING_REGISTER).c_str());
		SetDlgItemText(_hwnd, IDC_STATIC_LOG_IN_TITLE, _local.QueryString(IDS_STRING_TITLE).c_str());
	}

}