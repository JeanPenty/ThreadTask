#include "stdafx.h"
#include "Jean_ThreadBase.h"

namespace JeanUtility
{
	unsigned int __stdcall CJeanThreadBase::threadFunc(void *arg)
	{
		CJeanThreadBase *thread = (CJeanThreadBase *)arg;
		if (thread == 0) 
		{
			return 0; // error.
		}

		try
		{
			thread->run();
		}
		catch(...)
		{
			std::terminate();
		}

		thread->_done();

		return 0;
	}

	CJeanThreadBase::CJeanThreadBase()
		: m_bStarted(false)
		, m_bRunning(false)
		, m_hThread(0)
		, m_dwThreadID(0)
	{
	}

	CJeanThreadBase::~CJeanThreadBase() 
	{
	}

	bool CJeanThreadBase::start(size_t stackSize) 
	{
		CJeanThreadMutex::Lock guard(m_mtxState);

		if(m_bStarted)
		{
			assert(false);
			return false;
		}

		m_hThread = (HANDLE)_beginthreadex(NULL, stackSize, threadFunc, this, 0, (unsigned int*)&m_dwThreadID);
		if ( 0 == m_hThread )
		{
			assert(false);
			return false;
		}

		m_bStarted = true;
		m_bRunning = true;

		return true;
	}

	void CJeanThreadBase::join()
	{
		if(0 == m_hThread)
		{
			return;
		}

		DWORD rc = WaitForSingleObject(m_hThread, INFINITE);
		if(rc != WAIT_OBJECT_0)
		{
			assert(false);
		}

		detach();
	}

	void CJeanThreadBase::detach()
	{
		if(0 == m_hThread)
		{
			return;
		}

		CloseHandle(m_hThread);
	}

	void CJeanThreadBase::sleep(const JeanUtility::CJeanTime& timeout)
	{
		::Sleep(static_cast<DWORD>(timeout.toMilliSeconds()));
	}

	void CJeanThreadBase::yield()
	{
		::SwitchToThread();
	}

	DWORD CJeanThreadBase::getThreadId() const
	{
		CJeanThreadMutex::Lock guard(m_mtxState);
		return m_dwThreadID;
	}

	bool CJeanThreadBase::isAlive() const
	{
		CJeanThreadMutex::Lock guard(m_mtxState);
		return m_bRunning;
	}

	void CJeanThreadBase::_done()
	{
		CJeanThreadMutex::Lock guard(m_mtxState);
		m_bRunning = false;
	}

}// namespace JeanUtility