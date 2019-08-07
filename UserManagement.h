#pragma once
#include "stdafx.h"
#include "User.h"
#include "CustomExceptions.hpp"
#include <exception>

namespace CourseWork_WinApi
{
	enum LoginResult
	{
		SUCCESS, INVALIDUSER, INVALIDPASSWORD
	};

	class UserManagement
	{
	public:
		UserManagement();
		User * NewUser(tString userNickname, tString userPassword);
		User * GetUserByNickname(tString userNickname);
		const User * GetUserByNickname(tString userNickname) const;
		BOOL IsUserExists(tString userNickname);
		LoginResult LogIn(tString userNickname, tString userPassword);
		LoginResult LogIn(const User & user);

		~UserManagement();
		User & GetCurrentUser();
	private:
		std::vector<User>::iterator FindUser(tString nickName);
		BOOL ReadUser(LPBYTE buffer, DWORD dwSize, DWORD dwFrom, DWORD & dwNumberOfBytesRead);
		BOOL SafeUser(HANDLE hFile, User & user);
		std::vector<User> _users;
		INT _nCurrentUser;
	};

}