#include "stdafx.h"
#include "Jean_ThreadRecMutex.h"

#ifdef JEAN_WIN32
void JeanUtility::CJeanThreadRecMutex::lock() const
{
	EnterCriticalSection(&_mutex);
	if(++_count > 1)
	{
		LeaveCriticalSection(&_mutex);
	}
}

bool JeanUtility::CJeanThreadRecMutex::tryLock() const
{
	if(!TryEnterCriticalSection(&_mutex))
	{
		return false;
	}
	if(++_count > 1)
	{
		LeaveCriticalSection(&_mutex);
	}
	return true;
}

void JeanUtility::CJeanThreadRecMutex::unlock() const
{
	if(--_count == 0)
	{
		LeaveCriticalSection(&_mutex);
	}
}

void JeanUtility::CJeanThreadRecMutex::unlock(LockState& state) const
{
	state.count = _count;
	_count = 0;
	LeaveCriticalSection(&_mutex);
}

void JeanUtility::CJeanThreadRecMutex::lock(LockState& state) const
{
	EnterCriticalSection(&_mutex);
	_count = state.count;
}

#endif

bool JeanUtility::CJeanThreadRecMutex::willUnlock() const
{
	return _count == 1;
}
