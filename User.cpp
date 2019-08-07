#include "stdafx.h"
#include "User.h"

namespace CourseWork_WinApi
{
	User::User(tString name, tString password)
	{
		SetName(name);
		SetPassword(password);
	}

	User::User(const User & user)
	{
		_nickname = user._nickname;
		_password = user._password;
		_levelMap = user._levelMap;
	}

	User::User(User && user)
	{
		_nickname = std::move(user._nickname);
		_password = std::move(user._password);
		_levelMap = std::move(user._levelMap);
	}

	User & User::operator=(const User & user)
	{
		if (&user != this)
		{
			_nickname = user._nickname;
			_password = user._password;
			_levelMap = user._levelMap;
		}
		return *this;
	}

	User & User::operator=(User && user)
	{
		_nickname = std::move(user._nickname);
		_password = std::move(user._password);
		_levelMap = std::move(user._levelMap);
		return *this;
	}

	BOOL User::operator==(const User & user)
	{
		return this->_nickname == user._nickname && this->_password == user._password;
	}

	tString User::GetNickname() const
	{
		return _nickname;
	}

	void User::SetName(tString name)
	{
		_nickname = name;
	}

	tString User::GetPassword() const
	{
		return _password;
	}

	void User::SetPassword(tString password)
	{
		_password = password;
	}

	User & User::SetLevel(Language::Language language, int level)
	{
		_levelMap[language] = level;
		return *this;
	}


	INT User::GetLevel(Language::Language language)
	{
		return _levelMap[language];
	}

	User::~User()
	{
	}
}