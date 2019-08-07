#include "stdafx.h"
#include "Thread.h"

namespace CourseWork_WinApi
{
	CThread::CThread()
	{
		this->_hMainThread = ::GetCurrentThread();
		this->_dwMainThreadId = ::GetCurrentThreadId();
		this->_hThread = NULL;
		this->_dwThreadId = 0;
		this->_dwTimeOut = 2000; // milliseconds
	}

	CThread::~CThread()
	{
		if (this->IsCreated())
		{
			if (::WaitForSingleObject(this->_hThread, _dwTimeOut) == WAIT_TIMEOUT)
				::TerminateProcess(this->_hThread, 1);
			::CloseHandle(this->_hThread);
		}

	}

	BOOL CThread::CreateThread()
	{
		if (this->IsCreated() == FALSE)
		{
			ThreadWorkAround * ThreadParam = (ThreadWorkAround *) ::LocalAlloc(LMEM_FIXED, sizeof(ThreadWorkAround));
			if (ThreadParam == NULL)
				return FALSE;
			ThreadParam->ThisThread = this;
			this->_hThread = ::CreateThread(NULL, 0, this->runProcess, (void *)ThreadParam, 0, &this->_dwThreadId);
			return this->_hThread ? TRUE : FALSE;
		}
		return FALSE;
	}

	HANDLE CThread::GetThreadHandle()
	{
		return this->_hThread;
	}

	DWORD CThread::GetThreadId()
	{
		return this->_dwThreadId;
	}

	HANDLE	CThread::GetMainThreadHandle()
	{
		return this->_hMainThread;
	}

	DWORD CThread::GetMainThreadId()
	{
		return this->_dwMainThreadId;
	}

	VOID CThread::SetTimeOut(DWORD dwTimeOut)
	{
		this->_dwTimeOut = dwTimeOut;
	}

	DWORD CThread::GetTimeOut()
	{
		return this->_dwTimeOut;
	}

	BOOL CThread::IsCreated()
	{
		return (this->_hThread != NULL);
	}

	DWORD CALLBACK CThread::runProcess(LPVOID lpParam)
	{
		ThreadWorkAround * Param = static_cast<ThreadWorkAround *>(lpParam);
		CThread * Thread = Param->ThisThread;
		LocalFree(Param);
		return Thread->Process();
	}
}