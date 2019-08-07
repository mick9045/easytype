#include "stdafx.h"
#include "RussianTypingLanguage.h"

namespace CourseWork_WinApi
{
	RussianTypingLanguage::RussianTypingLanguage()
	{
		Initialize();
		_levels[ID_RUSSIAN_LEVEL_AO] = _T("���������������");
		_levels[ID_RUSSIAN_LEVEL_SPACEBAR] = _T("�� �� �� �� ��� ��� ���� ���� ���� ���� ���� ���� ����");
	}

	VOID RussianTypingLanguage::Initialize()
	{
		BaseInit();
		AddButton(IDC_BUTTON_BACK_QUOTE, _T('~'), Shift::YES);
		AddButton(IDC_BUTTON_BACK_QUOTE, _T('`'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_1, _T('!'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_1, _T('1'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_2, _T('"'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_2, _T('2'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_3, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_3, _T('3'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_4, _T(';'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_4, _T('4'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_5, _T('%'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_5, _T('5'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_6, _T(':'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_6, _T('6'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_7, _T('?'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_7, _T('7'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_8, _T('*'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_8, _T('8'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_9, _T('('), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_9, _T('9'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_0, _T(')'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_0, _T('0'), Shift::NO);
		AddButton(IDC_BUTTON_MINUS, _T('_'), Shift::YES);
		AddButton(IDC_BUTTON_MINUS, _T('-'), Shift::NO);
		AddButton(IDC_BUTTON_EQUAL, _T('+'), Shift::YES);
		AddButton(IDC_BUTTON_EQUAL, _T('='), Shift::NO);

		AddButton(IDC_BUTTON_KEY_Q, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Q, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_W, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_W, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_E, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_E, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_R, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_R, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_T, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_T, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_Y, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Y, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_U, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_U, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_I, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_I, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_O, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_O, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_P, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_P, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_BRACKET_LEFT, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_BRACKET_LEFT, _T('�'), Shift::NO);
		AddButton(IDC_BUTTON_BRACKET_RIGHT, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_BRACKET_RIGHT, _T('�'), Shift::NO);
		AddButton(IDC_BUTTON_BACKSLASH, _T('/'), Shift::YES);
		AddButton(IDC_BUTTON_BACKSLASH, _T('\\'), Shift::NO);
			
		AddButton(IDC_BUTTON_KEY_A, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_A, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_S, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_S, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_D, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_D, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_F, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_F, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_G, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_G, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_H, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_H, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_J, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_J, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_K, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_K, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_L, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_L, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_SEMICOLON, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_SEMICOLON, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_QUOTE, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_QUOTE, _T('�'), Shift::NO, FALSE);

		AddButton(IDC_BUTTON_KEY_Z, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Z, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_X, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_X, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_C, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_C, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_V, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_V, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_B, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_B, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_N, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_N, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_M, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_M, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_COMMA, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_COMMA, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_PERIOD, _T('�'), Shift::YES);
		AddButton(IDC_BUTTON_PERIOD, _T('�'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_SLASH, _T('.'), Shift::NO);
		AddButton(IDC_BUTTON_SLASH, _T(','), Shift::YES, FALSE);
	}
	Language::Language RussianTypingLanguage::Language()
	{
		return Language::Russian;
	}
}