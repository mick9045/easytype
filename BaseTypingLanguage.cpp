#include "stdafx.h"
#include "BaseTypingLanguage.h"

namespace CourseWork_WinApi
{
	const TypeButtonInfo * BaseTypingLanguage::operator[](TCHAR character)
	{
		std::vector<TypeButtonInfo>::iterator it;
		it = std::find_if(_buttonInfo.begin(), _buttonInfo.end(), [character](TypeButtonInfo & info) {
			return info.Character() == character;
		});
		if (it != _buttonInfo.end())
		{
			return &(*it);
		}
		return NULL;
	}
	VOID BaseTypingLanguage::InitKeyBoard(KeyboardDialog & keyboard)
	{
		HWND hKeyboard = keyboard.GetWindowHandle();
		keyboard.Reset();
		::SendMessage(hKeyboard, WM_SETREDRAW, FALSE, 0);
		for (auto it = _buttonInfo.begin(); it != _buttonInfo.end(); it++)
		{
			if (it->ShiftPressed() && it->Show())
			{
				tString txt(1, it->Character());
				::SetDlgItemText(hKeyboard, it->Id(), txt.c_str());
			}
		}
		for (auto it = _buttonInfo.begin(); it != _buttonInfo.end(); it++)
		{
			if (!it->ShiftPressed() && it->Show())
			{
				HWND hButton = GetDlgItem(hKeyboard, it->Id());
				tString txt = BaseDialogWindow::GetText(hButton);
				txt += TEXT("\n");
				txt += it->Character();
				::SetWindowText(hButton, txt.c_str());
			}
		}
		
		SendMessage(hKeyboard, WM_SETREDRAW, TRUE, 0);
		RedrawWindow(
			hKeyboard, NULL, NULL,
			RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN
		);
	}

	tString BaseTypingLanguage::LoadLevel( INT id_level, TextDialog & textDialog)
	{
		tString str = _levels[id_level];
		textDialog.SetText(str);
		return str;
	}

	tString BaseTypingLanguage::GetLevelText(INT id_level)
	{
		return _levels[id_level];
	}

	VOID BaseTypingLanguage::AddButton(UINT id, TCHAR character, Shift::Shift shift, BOOL bShow)
	{
		_buttonInfo.push_back(TypeButtonInfo(id, character, shift == Shift::YES ? TRUE : FALSE, bShow));
	}

	VOID BaseTypingLanguage::BaseInit()
	{
		AddButton(IDC_BUTTON_SPACE, _T(' '), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_ENTER, _T('\u23ce'), Shift::NO, FALSE);
		//AddButton(IDC_BUTTON_BACKSPACE, _T('\b'), Shift::NO, FALSE);
	}
}
