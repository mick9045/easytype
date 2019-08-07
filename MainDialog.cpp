#include "stdafx.h"
#include "MainDialog.h"
#include "UserLogInDialog.h"
#include <Richedit.h>
#include "RussianTypingLanguage.h"
#include "EnglishTypingLanguage.h"
#include <fstream>
#include <algorithm>
#include <codecvt>
#include <string>

#define IDT_TIMER_SPEED USER_TIMER_MINIMUM + 1

namespace CourseWork_WinApi
{

	MainDialog::MainDialog()
		:BaseDialogWindow(IDD_DIALOG_MAIN)
	{
		_typingLanguage = new EnglishTypingLanguage();
		_local.SetLanguage(Language::Russian);
		_iCurrentLevel = 0;
		_millisecondsStart = 0;
	}


	MainDialog::~MainDialog()
	{
		delete _typingLanguage;
	}

	INT_PTR MainDialog::DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
			HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
			HANDLE_MSG(hwnd, WM_DESTROY, Cls_OnDestroy);
			HANDLE_MSG(hwnd, WM_MOVE, Cls_OnMove);
			HANDLE_MSG(hwnd, WM_SIZE, Cls_OnSize);
			HANDLE_MSG(hwnd, WM_GETMINMAXINFO, Cls_OnGetMinMaxInfo);
			HANDLE_MSG(hwnd, WM_KEYDOWN, Cls_OnKey);
			HANDLE_MSG(hwnd, WM_CHAR, Cls_OnChar);
			HANDLE_MSG(hwnd, WM_CTLCOLORDLG, Cls_OnCtlColor);
			HANDLE_MSG(hwnd, WM_COMMAND, Cls_OnCommand);
			HANDLE_MSG(hwnd, WM_INITMENUPOPUP, Cls_OnInitMenuPopup);
			HANDLE_MSG(hwnd, WM_MENUSELECT, Cls_OnMenuSelect);
			HANDLE_MSG(hwnd, WM_TIMER, Cls_OnTimer);
		}
		return FALSE;
	}

	VOID MainDialog::Cls_OnDestroy(HWND hwnd)
	{
		PostQuitMessage(NULL);
	}

	VOID MainDialog::Cls_OnClose(HWND hwnd)
	{
		INT result = MessageBox(
			_hwnd,
			_local.QueryString(IDS_STRING_PROMPT_CLOSE).c_str(),
			_local.QueryString(IDS_STRING_PROMPT_CLOSE_TITLE).c_str(),
			MB_ICONINFORMATION | MB_OKCANCEL
		);
		if (result == IDOK)
		{
			Close();
		}
	}

	VOID MainDialog::Cls_OnInitMenuPopup(HWND hwnd, HMENU hMenu, UINT item, BOOL fSystemMenu)
	{
		if (hMenu == _hmKeyboardLanguage)
		{
			UINT uCheck = _typingLanguage->Language() == Language::English
				? ID_LEARNING_ENGLISH : ID_LEARNING_RUSSIAN;
		
			CheckMenuRadioItem(
				hMenu,
				ID_LEARNING_ENGLISH,
				ID_LEARNING_RUSSIAN,
				uCheck,
				MF_BYCOMMAND
			);
		}
		else if (hMenu == _hmUILanguage)
		{

			UINT uCheck = _local.GetLanguage() == Language::English
				? ID_INTERFACE_ENGLISH : ID_INTERFACE_RUSSIAN;
				CheckMenuRadioItem(
					hMenu,
					ID_INTERFACE_ENGLISH,
					ID_INTERFACE_RUSSIAN,
					uCheck,
					MF_BYCOMMAND
				);
		}
		else if (hMenu == _hmLevel)
		{
			if (_typingLanguage->Language() == Language::English)
			{
				EnableMenuItem(hMenu, 0, MF_ENABLED | MF_BYPOSITION);
				EnableMenuItem(hMenu, 1, MF_DISABLED | MF_BYPOSITION);
			}
			else
			{
				EnableMenuItem(hMenu, 1, MF_ENABLED | MF_BYPOSITION);
				EnableMenuItem(hMenu, 0, MF_DISABLED | MF_BYPOSITION);
			}
		}
		else if (hMenu == _hmEnLevel)
		{
			INT level = _userManagement.GetCurrentUser().GetLevel(Language::English);
			INT itemsCount = GetMenuItemCount(hMenu);
			for (int i = 1; i <= itemsCount; i++)
			{
				EnableMenuItem(
					hMenu,
					GetMenuItemID(hMenu, i - 1),
					i > level ? MF_GRAYED : MF_ENABLED
				);
			}
		}
		else if (hMenu == _hmRuLevel)
		{
			INT level = _userManagement.GetCurrentUser().GetLevel(Language::Russian);
			INT itemsCount = GetMenuItemCount(hMenu);
			for (int i = 1; i <= itemsCount; i++)
			{
				EnableMenuItem(
					hMenu,
					GetMenuItemID(hMenu, i - 1),
					i > level ? MF_GRAYED : MF_ENABLED
				);
			}
		}
	}

	VOID MainDialog::Cls_OnMenuSelect(HWND hwnd, HMENU hmenu, INT item, HMENU hmenuPopup, UINT flags)
	{
	}

	VOID MainDialog::Cls_OnTimer(HWND hwnd, UINT id)
	{
		switch (id)
		{
		case IDT_TIMER_SPEED:
			UpdateSpeedStat();
			break;
		default:
			break;
		}
	}

	VOID MainDialog::UpdateSpeedStat()
	{
		DWORD milliseconds = GetTickCount();
		DOUBLE minutes = ((milliseconds - _millisecondsStart) / 1000.0) / 60.0;
		if (_text.CursorPos() > 0)
		{
			_statistics.UpdateCPM(static_cast<INT>(_text.CursorPos() / minutes));
		}
		else
		{
			_statistics.UpdateCPM(0);
		}
	}

	BOOL MainDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		
		UserLogInDialog * userLoginDialog = new UserLogInDialog(_userManagement);
		BOOL bResult = (userLoginDialog->CreateModal() == IDOK);

		delete userLoginDialog;
		
		if (bResult != IDOK)
		{
			Close();
		}

		UpdateMenu();
		
		_keyboard.Create(_hwnd);
		_text.Create(_hwnd);
		_statistics.Create(_hwnd);
		
		
		_typingLanguage->InitKeyBoard(_keyboard);
		//  \u23ce\offset	
		
		SetWindowPos(_keyboard.hWindow(), NULL, 30, 300, 0, 0, SWP_NOSIZE);
		
		SetWindowPos(hwnd, NULL, 0, 0, 1024, 740, SWP_NOMOVE);
		//_text.SetText(TEXT("fffff \u23ce\offset jjjjjj fj fj fj fj fffff jjjjj jj jj ff ff jf jf jf"));
		
		return TRUE;
	}

	VOID MainDialog::Cls_OnMove(HWND hwnd, INT x, INT y)
	{
		return VOID();
	}

	VOID MainDialog::Cls_OnSize(HWND hwnd, UINT state, INT cx, INT cy)
	{
		switch (state)
		{
		case SIZE_RESTORED:
		case SIZE_MAXIMIZED:

			break;
		}
		if (state == SIZE_RESTORED || state == SIZE_MAXIMIZED)
		{
			AlignElements();
		}
	}

	void MainDialog::Cls_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo)
	{
		lpMinMaxInfo->ptMinTrackSize.x = 1024;
		lpMinMaxInfo->ptMinTrackSize.y = 740;
	}

	VOID MainDialog::Cls_OnKey(HWND hwnd, UINT vk, BOOL fDown, INT cRepeat, UINT flags)
	{
	}

	VOID MainDialog::Cls_OnChar(HWND hwnd, TCHAR ch, INT cRepeat)
	{
		if (!_iCurrentLevel)
		{
			return;
		}

		if (_millisecondsStart == 0)
		{
			_millisecondsStart = GetTickCount();
			SetTimer(_hwnd, IDT_TIMER_SPEED, 1000, NULL);
		}

		const TypeButtonInfo * nextCharInfo = (*_typingLanguage)[_text.NextCharacter()];
		if (nextCharInfo != NULL)
		{
			_keyboard.Select(nextCharInfo->Id(), nextCharInfo->ShiftPressed());
		}
		else
		{
			_keyboard.Reset();
		}
		
		if (ch == _T('\b'))
		{
			_text.Undo();
		}
		else if (ch == _T('\r') && _text.CurrentCharacter() == _T('\u23ce'))
		{
			_text.Right();
		}
		else if (ch == _text.CurrentCharacter())
		{
			_text.Right();
		}
		else
		{
			_text.Wrong();
		}

		
		if (_text.WrongSymbolsCount() > 0 && _text.CursorPos() > 0)
		{
			_statistics.UpdateAccuracy(
				100 * _text.RightSymbolsCount() / _text.CursorPos()
			);
		}
		else
		{
			_statistics.UpdateAccuracy(100);
		}

		if (_text.isEnd())
		{
			OnLevelEnd();
		}
	}

	HBRUSH MainDialog::Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, INT type)
	{
		return HBRUSH();
	}

	VOID MainDialog::Cls_OnCommand(HWND hwnd, INT id, HWND hwndCtl, UINT codeNotify)
	{
		if (codeNotify == 0)
		{
			switch (id)
			{
			case ID_INTERFACE_ENGLISH:
				_local.SetLanguage(Language::English);
				_statistics.UpdateUILanguage();
				UpdateMenu();
				break;
			case ID_INTERFACE_RUSSIAN:
				_local.SetLanguage(Language::Russian);
				_statistics.UpdateUILanguage();
				UpdateMenu();
				break;
			case ID_LEARNING_ENGLISH:
				if (_typingLanguage->Language() == Language::English)
				{
					break;
				}
				delete _typingLanguage;
				_typingLanguage = new EnglishTypingLanguage();
				_typingLanguage->InitKeyBoard(_keyboard);
				_iCurrentLevel = 0;
				_text.Reset();
				KillTimer(_hwnd, IDT_TIMER_SPEED);
				break;
			case ID_LEARNING_RUSSIAN:
				if (_typingLanguage->Language() == Language::Russian)
				{
					break;
				}
				delete _typingLanguage;
				_typingLanguage = new RussianTypingLanguage();
				_typingLanguage->InitKeyBoard(_keyboard);
				_iCurrentLevel = 0;
				_text.Reset();
				KillTimer(_hwnd, IDT_TIMER_SPEED);
				break;
			case ID_FILE_OPEN:
				OnOpenFile();
				break;
			default:
				CheckIfLevel(id);
				break;
			}
		}
		return VOID();
	}

	VOID MainDialog::OnOpenFile()
	{
		OPENFILENAME OpenFileName = {};
		LARGE_INTEGER fileSize;
		LPTSTR szFileFullPath = (LPTCH)LocalAlloc(LMEM_FIXED, sizeof(TCHAR) * MAX_PATH);
		ZeroMemory(szFileFullPath, sizeof(TCHAR) * MAX_PATH);

		OpenFileName.lStructSize = sizeof(OPENFILENAME);
		OpenFileName.hwndOwner = _hwnd;
		OpenFileName.lpstrFilter = TEXT("Text Files(*.txt)\0*.txt\0All Files(*.*)\0*.*\0");
		OpenFileName.lpstrFile = szFileFullPath;
		OpenFileName.nMaxFile = MAX_PATH;
		OpenFileName.lpstrInitialDir = TEXT("C:\\");
		OpenFileName.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		
		if (GetOpenFileName(&OpenFileName))
		{
			std::wfstream fileStream;
			std::locale locale(std::locale("Russian"), new std::codecvt_utf8<TCHAR>());
			fileStream.imbue(locale);
			tString text;
			fileStream.open(szFileFullPath, std::ios::in);
			if (fileStream.is_open())
			{
				
				/*std::wfstream::streampos begin, end;
				begin = fileStream.tellg();
				fileStream.seekg(0, fileStream.end);
				end = fileStream.tellg();
				WORD size = (end - begin) + 1;
				if (size == 0)
				{
					fileStream.close();
					return;
				}

				fileStream.seekg(0, fileStream.beg);
				LPTCH lptszTempBuff = (LPTCH)LocalAlloc(LMEM_FIXED, sizeof(TCHAR) * (size + 1));
				
				fileStream.read(lptszTempBuff, size);
				lptszTempBuff[size - 1] = TEXT('\0');
				text = tString(lptszTempBuff);
				LocalFree(lptszTempBuff);
				fileStream.close();
				*/
				tString str = _T("");
				while (std::getline(fileStream, str))
				{
					if (str[0] == 65279)
					{
						str.replace(0, 1, _TEXT(""));
					}
					text += str;
					text.push_back(_T('\n'));
				}

				tString search = _T("\n");
				tString replacement = _T("\u23ce\n");
				tString::size_type offset = 0;
				while ((offset = text.find(search, offset)) != std::string::npos)
				{
					text.replace(offset, search.size(), replacement);
					offset += replacement.size();
				}

				_iCurrentLevel = -1;
				_text.SetText(text);
				_keyboard.Reset();
				const TypeButtonInfo * nextCharInfo = (*_typingLanguage)[_text.CurrentCharacter()];
				if (nextCharInfo != NULL)
				{
					_keyboard.Select(nextCharInfo->Id(), nextCharInfo->ShiftPressed());
				}
				fileStream.close();
			}
			

			LocalFree(szFileFullPath);
		}
		return VOID();
	}

	VOID MainDialog::UpdateMenu()
	{

		HMENU hNewMenu = LoadMenu(
			GetModuleHandle(NULL),
			MAKEINTRESOURCE(IDR_MENU_MAIN)
		);
		HMENU hOldMenu = GetMenu(_hwnd);
		if (hOldMenu != NULL)
		{
			DestroyMenu(hOldMenu);
		}
		if (hNewMenu != NULL)
		{
			SetMenu(_hwnd, hNewMenu);
		}
		HMENU hmLangauge = GetSubMenu(hNewMenu, 1);
		_hmLevel = GetSubMenu(hNewMenu, 2);

		_hmUILanguage = GetSubMenu(hmLangauge, 0);
		_hmKeyboardLanguage = GetSubMenu(hmLangauge, 1);
		_hmEnLevel = GetSubMenu(_hmLevel, 0);
		_hmRuLevel = GetSubMenu(_hmLevel, 1);
	}

	VOID MainDialog::AlignElements()
	{
		HWND hwndRichEdit = GetDlgItem(_hwnd, IDC_RICHEDIT_TEXT);
		SIZE sizeRichEdit = GetClientSize(hwndRichEdit);
		SIZE windowSize = GetClientSize();
		SIZE sizeKeyboard = _keyboard.GetSize();
		SIZE sizeText = _text.GetSize();
		SIZE sizeStat = _statistics.GetSize();

		WORD offset = 30;

		MoveWindow(
			_text.GetWindowHandle(),
			windowSize.cx / 2 - _text.GetClientSize().cx / 2,
			_text.GetLocalPosition().y,
			sizeText.cx,
			sizeText.cy,
			TRUE
		);

		MoveWindow(
			_keyboard.GetWindowHandle(),
			windowSize.cx / 2 - _keyboard.GetClientSize().cx / 2,
			_keyboard.GetLocalPosition().y,
			sizeKeyboard.cx,
			sizeKeyboard.cy,
			TRUE
		);

		MoveWindow(
			_statistics.GetWindowHandle(),
			_keyboard.GetLocalPosition().x - 50,
			_text.GetLocalPosition().y + 50,
			sizeStat.cx,
			sizeStat.cy,
			TRUE
		);
	}

	BOOL MainDialog::CheckIfLevel(INT id)
	{
		if (_typingLanguage->LoadLevel(id, _text) != _T(""))
		{
			HMENU hMenu = NULL;
			switch (_typingLanguage->Language())
			{
			case Language::English:
				hMenu = _hmEnLevel;
				break;
			case Language::Russian:
				hMenu = _hmRuLevel;
				break;
			default:
				break;
			}
			_iCurrentLevel = GetMenuItemPosById(hMenu, id) + 1;
			_statistics.Reset();
			_keyboard.Reset();
			const TypeButtonInfo * nextCharInfo = (*_typingLanguage)[_text.CurrentCharacter()];
			if (nextCharInfo != NULL)
			{
				_keyboard.Select(nextCharInfo->Id(), nextCharInfo->ShiftPressed());
			}

			return TRUE;
		}
		return FALSE;
	}

	VOID MainDialog::OnLevelEnd()
	{
		KillTimer(_hwnd, IDT_TIMER_SPEED);
		UpdateSpeedStat();
		_millisecondsStart = 0;
		_keyboard.Reset();
		if (_statistics.Accuracy() > 80)
		{
			::MessageBox(
				_hwnd,
				_local.QueryString(IDS_STRING_LEVEL_COMPLETED).c_str(),
				_TEXT(""),
				MB_OK | MB_ICONINFORMATION
			);
			User & currentUser = _userManagement.GetCurrentUser();
			if (currentUser.GetLevel(_typingLanguage->Language()) == _iCurrentLevel)
			{
				currentUser.SetLevel(_typingLanguage->Language(), _iCurrentLevel + 1);
			}
		}
		else
		{
			::MessageBox(
				_hwnd,
				_local.QueryString(IDS_STRING_LEVEL_FAILED).c_str(),
				_TEXT(""),
				MB_OK | MB_ICONWARNING
			);
		}
		_iCurrentLevel = 0;
	}


}