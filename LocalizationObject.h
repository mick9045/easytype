#pragma once
#include "stdafx.h"

namespace CourseWork_WinApi
{
	namespace Language
	{
		enum Language
		{
			English, Russian
		};
	}

	class LocalizationObject
	{
	public:
		LocalizationObject();
		~LocalizationObject();
		Language::Language GetLanguage();
		VOID SetLanguage(Language::Language language);
		tString QueryString(UINT identifier);
	protected:
		Language::Language _language;
	private:

	};

}