#include "stdafx.h"
#include "KeyboardDialog.h"

namespace CourseWork_WinApi
{
	KeyboardDialog::KeyboardDialog()
		:BaseDialogWindow(IDD_DIALOG_KEYBOARD)
	{
		_lastHand = Hand::NONE;
		_bHands = TRUE;
		_uLastId = 0;
		_bLastTimeShift = FALSE;
		HINSTANCE hInst = GetModuleHandle(NULL);

		_bitmapsMap[IDB_BITMAP_LEFT_HAND] = LoadBitmap(
			hInst, 
			MAKEINTRESOURCE(IDB_BITMAP_LEFT_HAND)
		);
		_bitmapsMap[IDB_BITMAP_LEFT_HAND_THUMB] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_LEFT_HAND_THUMB)
		);
		_bitmapsMap[IDB_BITMAP_LEFT_HAND_MIDDLE] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_LEFT_HAND_MIDDLE)
		);
		_bitmapsMap[IDB_BITMAP_LEFT_HAND_RING] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_LEFT_HAND_RING)
		);
		_bitmapsMap[IDB_BITMAP_LEFT_HAND_LITTLE] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_LEFT_HAND_LITTLE)
		);
		_bitmapsMap[IDB_BITMAP_LEFT_HAND_POINTER] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_LEFT_HAND_POINTER)
		);

		_bitmapsMap[IDB_BITMAP_RIGHT_HAND] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_RIGHT_HAND)
		);
		_bitmapsMap[IDB_BITMAP_RIGHT_HAND_THUMB] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_RIGHT_HAND_THUMB)
		);
		_bitmapsMap[IDB_BITMAP_RIGHT_HAND_MIDDLE] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_RIGHT_HAND_MIDDLE)
		);
		_bitmapsMap[IDB_BITMAP_RIGHT_HAND_RING] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_RIGHT_HAND_RING)
		);
		_bitmapsMap[IDB_BITMAP_RIGHT_HAND_LITTLE] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_RIGHT_HAND_LITTLE)
		);
		_bitmapsMap[IDB_BITMAP_RIGHT_HAND_POINTER] = LoadBitmap(
			hInst,
			MAKEINTRESOURCE(IDB_BITMAP_RIGHT_HAND_POINTER)
		);
	}


	KeyboardDialog::~KeyboardDialog()
	{
		for (auto it = _bitmapsMap.begin(); it != _bitmapsMap.end(); ++it)
		{
			DeleteObject(it->second);
		}
	}

	INT_PTR KeyboardDialog::DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		
		switch (uMsg)
		{
			HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
			HANDLE_MSG(hwnd, WM_CTLCOLORDLG, Cls_OnCtlColor);
			HANDLE_MSG(hwnd, WM_CTLCOLORSTATIC, Cls_OnCtlColor);
		}
		return FALSE;
	}

	VOID KeyboardDialog::Select(UINT id, BOOL shift)
	{
		if (!_bHands)
		{
			_uLastId = 0;
			return;
		}
		UnselectLast();

		Hand::Hand hand = DetermineHand(id);
		Thinger::Thinger thinger;

		if (hand == Hand::NONE)
		{
			return;
		}
		
		Hand::Hand freeHand = (hand == Hand::LEFT ? Hand::RIGHT : Hand::LEFT);
		// Highlighting the key
		::SendDlgItemMessage(_hwnd, id, BM_SETSTATE, TRUE, NULL);

		thinger = DetermineThinger(id);
		SetHandImage(hand, thinger);

		if (shift == TRUE)
		{
			::SendDlgItemMessage(
				_hwnd,
				hand == Hand::LEFT ? IDC_BUTTON_SHIFT_RIGHT : IDC_BUTTON_SHIFT_LEFT,
				BM_SETSTATE,
				TRUE,
				NULL
			);
			SetHandImage(freeHand, Thinger::LITTLE);
		}
		else
		{
			SetHandImage(freeHand, Thinger::NONE);
		}


		_uLastId = id;
		_lastHand = hand;
		_bLastTimeShift = shift;
	


	}

	VOID KeyboardDialog::Reset()
	{
		SetHandImage(Hand::LEFT, Thinger::NONE);
		SetHandImage(Hand::RIGHT, Thinger::NONE);
		UnselectLast();
	}

	BOOL KeyboardDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		//SetActiveWindow(GetDlgItem(hwnd, IDC_BUTTON_KEY_A));
		::EnableWindow(hwnd, FALSE);
		//SendDlgItemMessage(hwnd, IDC_BUTTON_KEY_A, WM_SETFOCUS, NULL, NULL);
		SetHandImage(Hand::RIGHT, Thinger::NONE);
		SetHandImage(Hand::LEFT, Thinger::NONE);
		//ShowWindow(h, SW_HIDE);
		return TRUE;
	}

	HBRUSH KeyboardDialog::Cls_OnCtlColor(HWND hwnd, HDC hdc, HWND hwndChild, int type)
	{
		return GetStockBrush(WHITE_BRUSH);
	}

	Hand::Hand KeyboardDialog::DetermineHand(UINT controlId)
	{
		if (controlId < IDC_BUTTON_BACK_QUOTE ||
			controlId > IDC_BUTTON_CONTROL_RIGHT)
		{
			return Hand::NONE;
		}

		if ((controlId >= IDC_BUTTON_BACK_QUOTE && controlId <= IDC_BUTTON_DIGIT_5) ||
			(controlId >= IDC_BUTTON_TAB && controlId <= IDC_BUTTON_KEY_T) ||
			(controlId >= IDC_BUTTON_CAPSLOCK && controlId <= IDC_BUTTON_KEY_G) ||
			(controlId >= IDC_BUTTON_SHIFT_LEFT && controlId <= IDC_BUTTON_KEY_B) ||
			(controlId >= IDC_BUTTON_CONTROL_LEFT && controlId <= IDC_BUTTON_ALT_LEFT))
		{
			return Hand::LEFT;
		}
		else if (controlId == IDC_BUTTON_SPACE)
		{
			if (_lastHand == Hand::LEFT)
			{
				return Hand::RIGHT;
			}
			return Hand::LEFT;
		}
		

		return Hand::RIGHT;
	}

	Thinger::Thinger KeyboardDialog::DetermineThinger(UINT controlId)
	{
		Thinger::Thinger thinger;
		switch (controlId)
		{
			/*left*/
		case IDC_BUTTON_BACK_QUOTE:
		case IDC_BUTTON_TAB:
		case IDC_BUTTON_CAPSLOCK:
		case IDC_BUTTON_SHIFT_LEFT:
		case IDC_BUTTON_CONTROL_LEFT:

		case IDC_BUTTON_DIGIT_1:
		case IDC_BUTTON_KEY_Q:
		case IDC_BUTTON_KEY_A:
		case IDC_BUTTON_KEY_Z:
			thinger = Thinger::LITTLE;
			break;
			/*left*/
		case IDC_BUTTON_DIGIT_2:
		case IDC_BUTTON_KEY_W:
		case IDC_BUTTON_KEY_S:
		case IDC_BUTTON_KEY_X:
			thinger = Thinger::RING;
			break;
			/*left*/
		case IDC_BUTTON_DIGIT_3:
		case IDC_BUTTON_KEY_E:
		case IDC_BUTTON_KEY_D:
		case IDC_BUTTON_KEY_C:
			thinger = Thinger::MIDDLE;
			break;
			/*left*/
		case IDC_BUTTON_DIGIT_4:
		case IDC_BUTTON_KEY_R:
		case IDC_BUTTON_KEY_F:
		case IDC_BUTTON_KEY_V:

		case IDC_BUTTON_DIGIT_5:
		case IDC_BUTTON_KEY_T:
		case IDC_BUTTON_KEY_G:
		case IDC_BUTTON_KEY_B:
			thinger = Thinger::POINTER;
			break;
			/*middle*/
		case IDC_BUTTON_SPACE:
		case IDC_BUTTON_ALT_LEFT:
		case IDC_BUTTON_ALT_RIGHT:
			thinger = Thinger::THUMB;
			break;
			/*right*/
		case IDC_BUTTON_DIGIT_6:
		case IDC_BUTTON_KEY_Y:
		case IDC_BUTTON_KEY_H:
		case IDC_BUTTON_KEY_N:

		case IDC_BUTTON_DIGIT_7:
		case IDC_BUTTON_KEY_U:
		case IDC_BUTTON_KEY_J:
		case IDC_BUTTON_KEY_M:
			thinger = Thinger::POINTER;
			break;
			/*right*/
		case IDC_BUTTON_DIGIT_8:
		case IDC_BUTTON_KEY_I:
		case IDC_BUTTON_KEY_K:
		case IDC_BUTTON_COMMA:
			thinger = Thinger::MIDDLE;
			break;
			/*right*/
		case IDC_BUTTON_DIGIT_9:
		case IDC_BUTTON_KEY_O:
		case IDC_BUTTON_KEY_L:
		case IDC_BUTTON_PERIOD:
			thinger = Thinger::RING;
			break;
			/*right*/
		case IDC_BUTTON_DIGIT_0:
		case IDC_BUTTON_KEY_P:
		case IDC_BUTTON_SEMICOLON:
		case IDC_BUTTON_SLASH:

		case IDC_BUTTON_MINUS:
		case IDC_BUTTON_BRACKET_LEFT:
		case IDC_BUTTON_QUOTE:
		
		case IDC_BUTTON_EQUAL:
		case IDC_BUTTON_BRACKET_RIGHT:
		
		case IDC_BUTTON_BACKSPACE:
		case IDC_BUTTON_BACKSLASH:
		case IDC_BUTTON_ENTER:
		case IDC_BUTTON_SHIFT_RIGHT:
		case IDC_BUTTON_CONTROL_RIGHT:
			thinger = Thinger::LITTLE;
			break;
		default:
			thinger = Thinger::NONE;
			break;

		}
		return thinger;
	}

	BOOL KeyboardDialog::UnselectLast()
	{
		if (_uLastId != 0)
		{
			::SendDlgItemMessage(_hwnd, _uLastId, BM_SETSTATE, FALSE, NULL);
			if (_bLastTimeShift)
			{
				::SendDlgItemMessage(
					_hwnd,
					_lastHand == Hand::LEFT ? IDC_BUTTON_SHIFT_RIGHT : IDC_BUTTON_SHIFT_LEFT,
					BM_SETSTATE,
					FALSE,
					NULL
				);
				//ShowWindow(GetDlgItem(_hwnd, _lastHand == Hand::LEFT ? IDC_BUTTON_SHIFT_RIGHT : IDC_BUTTON_SHIFT_LEFT), SW_HIDE);
			}
			return true;
		}
		return false;
	}

	VOID KeyboardDialog::SetHandImage(Hand::Hand hand, Thinger::Thinger thinger)
	{
		if (hand == Hand::NONE)
		{
			return;
		}
		HWND hStatic;
		if (hand == Hand::LEFT)
		{
			hStatic = GetDlgItem(_hwnd, IDC_STATIC_LEFT_HAND);;
			switch (thinger)
			{
			case Thinger::THUMB:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_LEFT_HAND_THUMB]);
				break;
			case Thinger::POINTER:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_LEFT_HAND_POINTER]);
				break;
			case Thinger::MIDDLE:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_LEFT_HAND_MIDDLE]);
				break;
			case Thinger::RING:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_LEFT_HAND_RING]);
				break;
			case Thinger::LITTLE:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_LEFT_HAND_LITTLE]);
				break;
			default:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_LEFT_HAND]);
				break;
			}
		}
		else
		{
			hStatic = GetDlgItem(_hwnd, IDC_STATIC_RIGHT_HAND);;
			switch (thinger)
			{
			case Thinger::THUMB:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_RIGHT_HAND_THUMB]);
				break;
			case Thinger::POINTER:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_RIGHT_HAND_POINTER]);
				break;
			case Thinger::MIDDLE:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_RIGHT_HAND_MIDDLE]);
				break;
			case Thinger::RING:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_RIGHT_HAND_RING]);
				break;
			case Thinger::LITTLE:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_RIGHT_HAND_LITTLE]);
				break;
			default:
				SetStaticBitmap(hStatic, _bitmapsMap[IDB_BITMAP_RIGHT_HAND]);
				break;
			}
		}
	}

	HBITMAP KeyboardDialog::SetStaticBitmap(HWND hwndStatic, HBITMAP hBitmap)
	{
		LRESULT lResult = SendMessage(
			hwndStatic,
			STM_SETIMAGE,
			IMAGE_BITMAP,
			reinterpret_cast<LPARAM>(hBitmap)
		);
		return reinterpret_cast<HBITMAP>(lResult);
	}

}