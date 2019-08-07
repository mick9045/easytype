#include "stdafx.h"
#include "UserManagement.h"
#include <Strsafe.h>

namespace CourseWork_WinApi
{
	UserManagement::UserManagement()
	{
		_nCurrentUser = -1;

		LARGE_INTEGER fileSize;
		OFSTRUCT ofstruct;
		ofstruct.cBytes = sizeof(OFSTRUCT);
		HANDLE hFile = CreateFile(
			TEXT("users"),					// name of the write
			GENERIC_READ,					// open for writing
			0,								// do not share
			NULL,							// default security
			OPEN_ALWAYS,					// create new file only
			FILE_ATTRIBUTE_NORMAL,			// normal file
			NULL);							// no attr. template
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		GetFileSizeEx(hFile, &fileSize);
		if (fileSize.QuadPart == 0)
		{
			CloseHandle(hFile);
			return;
		}
		LPBYTE buffer = new BYTE[fileSize.LowPart];
		DWORD bytesRead = 0;
		DWORD from = 0;
		ReadFile(hFile, buffer, fileSize.LowPart, &bytesRead, NULL);
		while (ReadUser(buffer, fileSize.LowPart, from, bytesRead))
		{
			from += bytesRead;
		}
		CloseHandle(hFile);
		delete[] buffer;
	}

	User * UserManagement::NewUser(tString userName, tString userPassword)
	{
		if (GetUserByNickname(userName) == nullptr)
		{
			User user(userName, userPassword);
			user.SetLevel(Language::English, 1).SetLevel(Language::Russian, 1);

			_users.push_back(user);
			return &(_users[_users.size() - 1]);
		}
		return nullptr;
	}

	User * UserManagement::GetUserByNickname(tString nickName)
	{
		std::vector<User>::iterator it = FindUser(nickName);
		//check if something is found return the value;
		if (it != _users.end())
		{
			return &(*it);
		}
		//otherwise return nullptr
		return nullptr;
	}

	const User * UserManagement::GetUserByNickname(tString userNickname) const
	{
		return const_cast<UserManagement*>(this)->GetUserByNickname(userNickname);
	}

	BOOL UserManagement::IsUserExists(tString userNickname)
	{
		return (GetUserByNickname(userNickname) != nullptr);
	}

	LoginResult UserManagement::LogIn(tString userNickName, tString userPassword)
	{
		std::vector<User>::iterator it = FindUser(userNickName);
		if (it != _users.end())
		{
			User & user = (*it);
			if (user.GetPassword() != userPassword)
			{
				return LoginResult::INVALIDPASSWORD;
			}

			_nCurrentUser = it - _users.begin();
			return LoginResult::SUCCESS;
		}
		return LoginResult::INVALIDUSER;
	}

	LoginResult UserManagement::LogIn(const User & user)
	{
		std::vector<User>::iterator it = std::find(_users.begin(), _users.end(), user);
		if (it != _users.end())
		{
			_nCurrentUser = it - _users.begin();
			return LoginResult::SUCCESS;
		}
		return LoginResult::INVALIDUSER;
	}


	UserManagement::~UserManagement()
	{
		HANDLE hFile = CreateFile(
			_T("users"),							// name of the write
			GENERIC_WRITE,							// open for writing
			0,										// do not share
			NULL,									// default security
			CREATE_ALWAYS,							// create new file only
			FILE_ATTRIBUTE_NORMAL,					// normal file
			NULL
		);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return;
		}
		for (auto user : _users)
		{
			SafeUser(hFile, user);
		}
		CloseHandle(hFile);
	}

	User & UserManagement::GetCurrentUser()
	{
		if (_nCurrentUser == -1)
		{
			throw cex::NoCurrentUserException();
		}
		return _users[_nCurrentUser];
	}

	std::vector<User>::iterator UserManagement::FindUser(tString nickName)
	{
		return std::find_if(
			_users.begin(), _users.end(),
			[&nickName](const User & user) { return user.GetNickname() == nickName; }
		);
	}

	BOOL UserManagement::ReadUser(LPBYTE buffer, DWORD size, DWORD from, DWORD & numberOfBytesRead)
	{
		if (from >= size)
		{
			return FALSE;
		}
		LPBYTE lpBufferEnd = buffer + size;
		LPTSTR name;
		INT nameLen;
		LPTSTR surname;
		INT surnameLen;
		INT iLanguagesCount;

		LPTSTR str = reinterpret_cast<LPTSTR>(buffer + from);
		
		nameLen = ::lstrlen(str) + 1;
		if (reinterpret_cast<LPBYTE>(str + nameLen) > lpBufferEnd)
		{
			numberOfBytesRead = 0;
			return FALSE;
		}
		name = new TCHAR[nameLen];
		::StringCchCopy(name, nameLen, str);
		str += nameLen;
		surnameLen = ::lstrlen(str) + 1;
		if (reinterpret_cast<LPBYTE>(str + surnameLen) > lpBufferEnd)
		{
			numberOfBytesRead = 0;
			return FALSE;
		}
		surname = new TCHAR(surnameLen);
		::StringCchCopy(surname, surnameLen, str);
		str += surnameLen;

		User user = User(tString(name), tString(surname));

		LPBYTE buffer2 = reinterpret_cast<LPBYTE>(str);

		
		if (buffer2 + sizeof(INT) > lpBufferEnd)
		{
			numberOfBytesRead = buffer2 - (buffer + from);
			_users.push_back(user);
			return TRUE;
		}

		

		::CopyMemory(&iLanguagesCount, buffer2, sizeof(INT));
		buffer2 += sizeof(INT);

		Language::Language language;
		INT level;
		for (INT i = 0; i < iLanguagesCount; i++)
		{
			if (buffer2 + sizeof(INT) * 2 > lpBufferEnd)
			{
				break;
			}
			::CopyMemory(&language, buffer2, sizeof(INT));
			buffer2 += sizeof(INT);
			::CopyMemory(&level, buffer2, sizeof(INT));
			buffer2 += sizeof(INT);
			user.SetLevel(language, level);
		}
		numberOfBytesRead = buffer2 - (buffer + from);
		_users.push_back(user);
		return TRUE;
	}

	BOOL UserManagement::SafeUser(HANDLE hFile, User & user)
	{
		DWORD dwBytesWritten;
		BOOL bResult;
		INT iNumberOfLanguages = 2;
		//writing name
		bResult = WriteFile(
			hFile,
			user.GetNickname().c_str(),
			(user.GetNickname().length() + 1) * sizeof(TCHAR),
			&dwBytesWritten,
			NULL
		);
		if (!bResult)
		{
			return FALSE;
		}
		//writing password
		bResult = WriteFile(
			hFile,
			user.GetPassword().c_str(),
			(user.GetPassword().length() + 1) * sizeof(TCHAR),
			&dwBytesWritten,
			NULL
		);
		if (!bResult)
		{
			return FALSE;
		}

		//writing count of learning languages
		bResult = WriteFile(
			hFile,
			&iNumberOfLanguages,
			sizeof(INT),
			&dwBytesWritten,
			NULL
		);
		if (!bResult)
		{
			return FALSE;
		}

		Language::Language language;
		INT level;

		//writing english language result
		language = Language::English;
		level = user.GetLevel(language);

		WriteFile(
			hFile,
			&language,
			sizeof(INT),
			&dwBytesWritten,
			NULL
		);
		WriteFile(
			hFile,
			&level,
			sizeof(INT),
			&dwBytesWritten,
			NULL
		);

		language = Language::Russian;
		level = user.GetLevel(language);

		//writing russian language result
		WriteFile(
			hFile,
			&language,
			sizeof(INT),
			&dwBytesWritten,
			NULL
		);
		WriteFile(
			hFile,
			&level,
			sizeof(INT),
			&dwBytesWritten,
			NULL
		);

		return TRUE;
	}
}
