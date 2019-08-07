#pragma once
#include "BaseTypingLanguage.h"

namespace CourseWork_WinApi
{
	class RussianTypingLanguage :
		public BaseTypingLanguage
	{
	public:
		RussianTypingLanguage();
		// Inherited via BaseTypingLanguage
	protected:
		virtual VOID Initialize() override;

		// Inherited via BaseTypingLanguage
		virtual Language::Language Language() override;
	};

}