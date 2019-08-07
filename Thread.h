#pragma once
#include "stdafx.h"

namespace CourseWork_WinApi
{
	class CThread
	{
	public:
		CThread();
		virtual ~CThread();
		BOOL CreateThread();
		HANDLE	GetThreadHandle();
		DWORD	GetThreadId();
		HANDLE	GetMainThreadHandle();
		DWORD	GetMainThreadId();
		VOID SetTimeOut(DWORD dwTimeOut);
		DWORD GetTimeOut();
		BOOL IsCreated();
	protected:
		virtual DWORD Process() = 0;
		DWORD		_dwThreadId;
		HANDLE		_hThread;
		DWORD		_dwMainThreadId;
		HANDLE		_hMainThread;
	private:
		static DWORD CALLBACK runProcess(LPVOID lpParam);
		DWORD _dwTimeOut;
	};

	struct ThreadWorkAround
	{
		CThread * ThisThread;
	};
}