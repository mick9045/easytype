#include "stdafx.h"
#include "EnglishTypingLanguage.h"

namespace CourseWork_WinApi
{
	EnglishTypingLanguage::EnglishTypingLanguage()
	{
		Initialize();
		_levels[ID_ENGLISH_LEVEL_EN_FJ] = _T("ffffffjjjjjjjjjj");
		_levels[ID_ENGLISH_LEVEL_EN_SPACEBAR] = _T("jjjjjj fj fj fj fj fffff jjjjj jj jj ff ff jf jf jf");
		
	}


	EnglishTypingLanguage::~EnglishTypingLanguage()
	{
		
	}

	VOID EnglishTypingLanguage::Initialize()
	{
		BaseInit();
		AddButton(IDC_BUTTON_BACK_QUOTE, _T('~'), Shift::YES);
		AddButton(IDC_BUTTON_BACK_QUOTE, _T('`'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_1, _T('!'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_1, _T('1'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_2, _T('@'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_2, _T('2'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_3, _T('#'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_3, _T('3'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_4, _T('$'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_4, _T('4'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_5, _T('%'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_5, _T('5'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_6, _T('^'), Shift::YES);
		AddButton(IDC_BUTTON_DIGIT_6, _T('6'), Shift::NO);
		AddButton(IDC_BUTTON_DIGIT_7, _T('&'), Shift::YES);
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

		AddButton(IDC_BUTTON_KEY_Q, _T('Q'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Q, _T('q'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_W, _T('W'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_W, _T('w'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_E, _T('E'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_E, _T('e'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_R, _T('R'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_R, _T('r'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_T, _T('T'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_T, _T('t'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_Y, _T('Y'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Y, _T('y'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_U, _T('U'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_U, _T('u'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_I, _T('I'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_I, _T('i'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_O, _T('O'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_O, _T('o'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_P, _T('P'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_P, _T('p'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_BRACKET_LEFT, _T('{'), Shift::YES);
		AddButton(IDC_BUTTON_BRACKET_LEFT, _T('['), Shift::NO);
		AddButton(IDC_BUTTON_BRACKET_RIGHT, _T('}'), Shift::YES);
		AddButton(IDC_BUTTON_BRACKET_RIGHT, _T(']'), Shift::NO);
		AddButton(IDC_BUTTON_BACKSLASH, _T('|'), Shift::YES);
		AddButton(IDC_BUTTON_BACKSLASH, _T('\\'), Shift::NO);

		AddButton(IDC_BUTTON_KEY_A, _T('A'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_A, _T('a'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_S, _T('S'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_S, _T('s'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_D, _T('D'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_D, _T('d'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_F, _T('F'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_F, _T('f'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_G, _T('G'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_G, _T('g'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_H, _T('H'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_H, _T('h'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_J, _T('J'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_J, _T('j'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_K, _T('K'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_K, _T('k'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_L, _T('L'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_L, _T('l'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_SEMICOLON, _T(':'), Shift::YES);
		AddButton(IDC_BUTTON_SEMICOLON, _T(';'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_QUOTE, _T('"'), Shift::YES);
		AddButton(IDC_BUTTON_QUOTE, _T('\''), Shift::NO, FALSE);

		AddButton(IDC_BUTTON_KEY_Z, _T('Z'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Z, _T('z'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_X, _T('X'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_X, _T('x'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_C, _T('C'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_C, _T('c'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_V, _T('V'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_V, _T('v'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_B, _T('B'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_B, _T('b'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_N, _T('N'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_N, _T('n'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_M, _T('M'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_M, _T('m'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_COMMA, _T('<'), Shift::YES);
		AddButton(IDC_BUTTON_COMMA, _T(','), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_PERIOD, _T('<'), Shift::YES);
		AddButton(IDC_BUTTON_PERIOD, _T(','), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_SLASH, _T('?'), Shift::YES);
		AddButton(IDC_BUTTON_SLASH, _T('/'), Shift::NO, FALSE);
	}

	Language::Language EnglishTypingLanguage::Language()
	{
		return Language::English;
	}
}