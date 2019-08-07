#pragma once
#include "BaseDialogWindow.h"
#include "stdafx.h"
#include <Richedit.h>

namespace CourseWork_WinApi
{
	class TextDialog
		: public BaseDialogWindow
	{
	public:
		TextDialog();
		~TextDialog();
		virtual INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		VOID SetText(tString string);
		BOOL Wrong();
		BOOL Right();
		BOOL isEnd();
		BOOL Undo();
		INT RightSymbolsCount();
		INT WrongSymbolsCount();
		TCHAR CurrentCharacter();
		TCHAR NextCharacter();
		INT CursorPos();
		VOID Reset();
	protected:
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		VOID Select(LONG cpMin, LONG cpMax);
		VOID ColorSelection(COLORREF text, COLORREF background);
		VOID UnderlineSelection();
		VOID ShowCursor();

		COLORREF _unprintedText;
		COLORREF _printedText;
		COLORREF _wrongText;
	private:
		size_t _nCursor;
		tString _text;
		std::vector<INT> _vecWrongSymbolsPos;
		/*resources*/
		HFONT _hfont;
		
	};

}