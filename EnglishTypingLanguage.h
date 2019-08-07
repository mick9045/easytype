#pragma once
#include "BaseTypingLanguage.h"

namespace CourseWork_WinApi
{
	class EnglishTypingLanguage :
		public BaseTypingLanguage
	{
	public:
		EnglishTypingLanguage();
		~EnglishTypingLanguage();
	protected:
		// Inherited via BaseTypingLanguage
		virtual VOID Initialize() override;

		// Inherited via BaseTypingLanguage
		virtual Language::Language Language() override;
	};

}