#pragma once

#include <vector>
#include "TypeButtonInfo.h"
#include "BaseDialogWindow.h"
#include "TextDialog.h"
#include "KeyboardDialog.h"
#include "GameStatisticsDialog.h"

namespace CourseWork_WinApi
{
	namespace Shift
	{
		enum Shift
		{
			NO, YES
		};
	}

	class BaseTypingLanguage
	{
	public:
		const TypeButtonInfo * operator[](TCHAR character);
		VOID InitKeyBoard(KeyboardDialog & keyboard);
		tString LoadLevel(INT id_level, TextDialog & textDialog);
		tString GetLevelText(INT id_level);
		virtual Language::Language Language() = 0;
	protected:
		VOID AddButton(UINT id, TCHAR character, Shift::Shift shift, BOOL bShow = TRUE);
		VOID BaseInit();
		virtual VOID Initialize() = 0;

		std::map<INT, tString> _levels;
	private:
		std::vector<TypeButtonInfo> _buttonInfo;
	};
}


