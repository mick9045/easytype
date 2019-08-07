#include "stdafx.h"
#include "TextDialog.h"

namespace CourseWork_WinApi
{
	TextDialog::TextDialog()
		:BaseDialogWindow(IDD_DIALOG_TEXT)
	{
		_nCursor = 0;
		_printedText = RGB(0, 0, 0);
		_wrongText = RGB(239, 83, 80);
		_unprintedText = RGB(147, 147, 147);
	}


	TextDialog::~TextDialog()
	{
		DeleteObject(_hfont);
		RemoveFontResource(_TEXT("DejaVuSansMono.ttf"));
	}

	INT_PTR TextDialog::DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
		}
		return FALSE;
	}

	VOID TextDialog::SetText(tString string)
	{
		Select(0, -1);
		ColorSelection(_unprintedText, RGB(255, 255, 255));
		SendDlgItemMessage(
			_hwnd,
			IDC_RICHEDIT_TEXT,
			EM_REPLACESEL,
			0,
			reinterpret_cast<LPARAM>(string.c_str())
		);
		Select(-1, 0);
		_vecWrongSymbolsPos.clear();
		_nCursor = 0;
		ShowCursor();
		_text = string;
	}

	
	BOOL TextDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		EnableWindow(hwnd, FALSE);
		/*Setting font*/
		HWND hRich = GetDlgItem(hwnd, IDC_RICHEDIT_TEXT);
		LOGFONT LogFont;
		::ZeroMemory(&LogFont, sizeof(LOGFONT));
		
		LogFont.lfHeight = _dpiScale.Scale(44);
		LogFont.lfQuality = CLEARTYPE_QUALITY;
		AddFontResource(TEXT("fonts\\DejaVuSansMono.ttf"));
		LogFont.lfPitchAndFamily = FIXED_PITCH  | FF_MODERN;
		::lstrcpy(LogFont.lfFaceName, TEXT("DejaVu Sans Mono"));
		HFONT _hfont = ::CreateFontIndirect(&LogFont);
		::SendMessage(
			hRich,
			WM_SETFONT,
			reinterpret_cast<WPARAM>(_hfont),
			MAKELPARAM(TRUE, NULL)
		);
		
		Select(0, -1);
		ColorSelection(_unprintedText, RGB(255, 255, 255));
		
		
		return 0;
	}

	VOID TextDialog::Select(LONG cpMin, LONG cpMax)
	{
		//EnableWindow(_hwnd, true);
		SetFocus(_hwnd);
		CHARRANGE range{ cpMin, cpMax };
		HWND hwndEdit = GetDlgItem(_hwnd, IDC_RICHEDIT_TEXT);
		//SetFocus(hwndEdit);
		
		SendMessage(
			hwndEdit,
			EM_EXSETSEL,
			NULL,
			reinterpret_cast<LPARAM>(&range)
		);
		return void();
	}
	VOID TextDialog::ColorSelection(COLORREF textColor, COLORREF backgroundColor)
	{
		
		CHARFORMAT2 chrfrm;
		ZeroMemory(&chrfrm, sizeof(CHARFORMAT2));
		chrfrm.cbSize = sizeof(CHARFORMAT2);
		chrfrm.dwMask = CFM_COLOR | CFM_BACKCOLOR;
		chrfrm.crTextColor = textColor;
		chrfrm.crBackColor = backgroundColor;
		SendDlgItemMessage(
			_hwnd,
			IDC_RICHEDIT_TEXT,
			EM_SETCHARFORMAT,
			SCF_SELECTION,
			(LPARAM)&chrfrm
		);
	}
	VOID TextDialog::UnderlineSelection()
	{
		CHARFORMAT2 chrfrm;
		ZeroMemory(&chrfrm, sizeof(CHARFORMAT2));
		chrfrm.cbSize = sizeof(CHARFORMAT2);
		chrfrm.dwMask = CFM_UNDERLINE;
		chrfrm.dwEffects = CFE_UNDERLINE;
		SendDlgItemMessage(
			_hwnd,
			IDC_RICHEDIT_TEXT,
			EM_SETCHARFORMAT,
			SCF_SELECTION,
			(LPARAM)&chrfrm
		);
	}

	BOOL TextDialog::Wrong()
	{
		if (isEnd())
		{
			return FALSE;
		}
		Select(_nCursor, _nCursor + 1);
		_vecWrongSymbolsPos.push_back(_nCursor);
		ColorSelection(RGB(255, 255, 255), _wrongText);
		if (CurrentCharacter() == _T('\u23ce'))
		{
			_nCursor++;
		}
		_nCursor++;
		ShowCursor();
		return TRUE;
	}

	BOOL TextDialog::Right()
	{
		if (isEnd())
		{
			return FALSE;
		}
		
		Select(_nCursor, _nCursor + 1);
		ColorSelection(_printedText, RGB(255, 255, 255));
		if (CurrentCharacter() == _T('\u23ce'))
		{
			_nCursor++;
		}
		_nCursor++;
		ShowCursor();
		return TRUE;
	}

	BOOL TextDialog::isEnd()
	{
		return _nCursor > _text.length() - 1;
	}

	BOOL TextDialog::Undo()
	{
		if (_nCursor > 0)
		{
			ColorSelection(_unprintedText, RGB(255, 255, 255));
			_nCursor--;
			if (CurrentCharacter() == '\n')
			{
				_nCursor--;
			}
			if (_vecWrongSymbolsPos.size() > 0 &&
				*(_vecWrongSymbolsPos.end() - 1) == _nCursor)
			{
				_vecWrongSymbolsPos.pop_back();
			}
			ShowCursor();
			return TRUE;
		}
		return FALSE;
	}

	INT TextDialog::RightSymbolsCount()
	{
		return _nCursor - _vecWrongSymbolsPos.size();
	}

	INT TextDialog::WrongSymbolsCount()
	{
		return _vecWrongSymbolsPos.size();
	}

	TCHAR TextDialog::CurrentCharacter()
	{
		if (!isEnd())
		{
			return _text[_nCursor];
		}
		return _T('\0');
	}

	TCHAR TextDialog::NextCharacter()
	{
		if (_nCursor < _text.length() - 1)
		{
			return _text[_nCursor + 1];
		}
		return _T('\0');
	}

	INT TextDialog::CursorPos()
	{
		return _nCursor;
	}

	VOID TextDialog::Reset()
	{
		Select(0, -1);
		ColorSelection(_unprintedText, RGB(255, 255, 255));
		SendDlgItemMessage(
			_hwnd,
			IDC_RICHEDIT_TEXT,
			EM_REPLACESEL,
			0,
			reinterpret_cast<LPARAM>(_T(""))
		);
		_nCursor = 0;
		Select(-1, 0);
		_vecWrongSymbolsPos.clear();
		_text.clear();
	}

	VOID TextDialog::ShowCursor()
	{
		if (isEnd())
		{
			return;
		}
		HWND rich = GetDlgItem(_hwnd, IDC_RICHEDIT_TEXT);
		INT line = SendMessage(rich, EM_LINEFROMCHAR, _nCursor, NULL);
		INT firstVisibleLine = SendMessage(rich, EM_GETFIRSTVISIBLELINE, NULL, NULL);
		if (line - 1 > firstVisibleLine)
		{
			SendMessage(rich, EM_LINESCROLL, NULL, line - 1 - firstVisibleLine);
		}
		
		Select(_nCursor, _nCursor + 1);
		ColorSelection(RGB(255, 255, 255), RGB(33, 150, 243));
	}

	
}