#include "stdafx.h"
#include "RussianTypingLanguage.h"

namespace CourseWork_WinApi
{
	RussianTypingLanguage::RussianTypingLanguage()
	{
		Initialize();
		_levels[ID_RUSSIAN_LEVEL_AO] = _T("àààààààîîîîîîîî");
		_levels[ID_RUSSIAN_LEVEL_SPACEBAR] = _T("àà îî àà îî ààà îîî àààà îîîî ààîî ààîî îîàà îààî àîàî");
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
		AddButton(IDC_BUTTON_DIGIT_3, _T('¹'), Shift::YES);
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

		AddButton(IDC_BUTTON_KEY_Q, _T('É'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Q, _T('é'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_W, _T('Ö'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_W, _T('ö'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_E, _T('Ó'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_E, _T('ó'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_R, _T('Ê'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_R, _T('ê'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_T, _T('Å'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_T, _T('å'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_Y, _T('Í'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Y, _T('í'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_U, _T('Ã'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_U, _T('ã'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_I, _T('Ø'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_I, _T('ø'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_O, _T('Ù'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_O, _T('ù'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_P, _T('Ç'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_P, _T('ç'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_BRACKET_LEFT, _T('Õ'), Shift::YES);
		AddButton(IDC_BUTTON_BRACKET_LEFT, _T('õ'), Shift::NO);
		AddButton(IDC_BUTTON_BRACKET_RIGHT, _T('Ú'), Shift::YES);
		AddButton(IDC_BUTTON_BRACKET_RIGHT, _T('ú'), Shift::NO);
		AddButton(IDC_BUTTON_BACKSLASH, _T('/'), Shift::YES);
		AddButton(IDC_BUTTON_BACKSLASH, _T('\\'), Shift::NO);
			
		AddButton(IDC_BUTTON_KEY_A, _T('Ô'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_A, _T('ô'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_S, _T('Û'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_S, _T('û'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_D, _T('Â'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_D, _T('â'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_F, _T('À'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_F, _T('à'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_G, _T('Ï'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_G, _T('ï'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_H, _T('Ð'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_H, _T('ð'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_J, _T('Î'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_J, _T('î'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_K, _T('Ë'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_K, _T('ë'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_L, _T('Ä'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_L, _T('ä'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_SEMICOLON, _T('Æ'), Shift::YES);
		AddButton(IDC_BUTTON_SEMICOLON, _T('æ'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_QUOTE, _T('Ý'), Shift::YES);
		AddButton(IDC_BUTTON_QUOTE, _T('ý'), Shift::NO, FALSE);

		AddButton(IDC_BUTTON_KEY_Z, _T('ß'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_Z, _T('ÿ'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_X, _T('×'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_X, _T('÷'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_C, _T('Ñ'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_C, _T('ñ'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_V, _T('Ì'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_V, _T('ì'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_B, _T('È'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_B, _T('è'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_N, _T('Ò'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_N, _T('ò'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_KEY_M, _T('Ü'), Shift::YES);
		AddButton(IDC_BUTTON_KEY_M, _T('ü'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_COMMA, _T('Á'), Shift::YES);
		AddButton(IDC_BUTTON_COMMA, _T('á'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_PERIOD, _T('Þ'), Shift::YES);
		AddButton(IDC_BUTTON_PERIOD, _T('þ'), Shift::NO, FALSE);
		AddButton(IDC_BUTTON_SLASH, _T('.'), Shift::NO);
		AddButton(IDC_BUTTON_SLASH, _T(','), Shift::YES, FALSE);
	}
	Language::Language RussianTypingLanguage::Language()
	{
		return Language::Russian;
	}
}