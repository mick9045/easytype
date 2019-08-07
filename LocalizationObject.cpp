#include "stdafx.h"
#include "LocalizationObject.h"

namespace CourseWork_WinApi
{
	LocalizationObject::LocalizationObject()
	{
	}


	LocalizationObject::~LocalizationObject()
	{
	}

	Language::Language LocalizationObject::GetLanguage()
	{
		return _language;
	}

	VOID LocalizationObject::SetLanguage(Language::Language language)
	{
		_language = language;
		switch (language)
		{
		case Language::English:
			::SetThreadUILanguage(
				MAKELCID(LANG_ENGLISH, SUBLANG_NEUTRAL)
			);
			break;
		case Language::Russian:
			::SetThreadUILanguage(
				MAKELCID(LANG_RUSSIAN, SUBLANG_NEUTRAL)
			);
			break;
		}
	}

	tString CourseWork_WinApi::LocalizationObject::QueryString(UINT identifier)
	{
		LPTSTR p = nullptr;
		int len = ::LoadString(NULL, identifier, reinterpret_cast<LPTSTR>(&p), 0);
		if (len > 0)
		{
			return tString(p, static_cast<size_t>(len));
		}

		return tString();
	}
}