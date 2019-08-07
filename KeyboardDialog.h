#pragma once
#include "BaseDialogWindow.h"


namespace CourseWork_WinApi
{
	namespace Hand
	{
		enum Hand
		{
			NONE, RIGHT, LEFT
		};
	}

	namespace Thinger
	{
		enum Thinger
		{
			NONE, THUMB, POINTER, MIDDLE, RING, LITTLE
		};
	}

	class KeyboardDialog :
		public BaseDialogWindow
	{
	public:
		KeyboardDialog();
		~KeyboardDialog();
		virtual INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		VOID Select(UINT id, BOOL shift = false);
		VOID Reset();
	protected:
		/**/
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
		HBRUSH Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type);
		/**/
		Hand::Hand DetermineHand(UINT controlId);
		Thinger::Thinger DetermineThinger(UINT controlId);
		VOID SetHandImage(Hand::Hand hand, Thinger::Thinger thinger);
		BOOL UnselectLast();
	private:
		inline HBITMAP SetStaticBitmap(HWND hwndStatic, HBITMAP hBitmap);
		/**/
		std::map<LONG, HBITMAP> _bitmapsMap;
		Hand::Hand _lastHand;
		UINT _uLastId;
		BOOL _bLastTimeShift;

		/*settings*/
		BOOL _bHands;

	};

}