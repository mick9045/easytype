#pragma once
#include "stdafx.h"
#include "LocalizationObject.h"


namespace CourseWork_WinApi
{
	class User
	{
	public:
		User(tString name, tString password);
		User( const User & user);
		User(User && user);

		User & operator=(const User & user);
		User & operator=(User && user);
		BOOL operator==(const User & user);
		tString GetNickname() const;
		VOID SetName(tString name);
		tString GetPassword() const;
		VOID SetPassword(tString password);
		User & SetLevel(Language::Language language, int level);
		INT GetLevel(Language::Language langauge);
		~User();
	private:
		tString _nickname;
		tString _password;
		Language::Language _Interface;
		std::map<Language::Language, INT> _levelMap;
	};

}