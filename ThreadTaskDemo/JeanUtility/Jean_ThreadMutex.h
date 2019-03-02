#pragma once
#ifndef __JEAN_THREADMUTEX_H__
#define __JEAN_THREADMUTEX_H__

#include "Jean_Base.h"
#include "Jean_Lock.h"
#include "Jean_BaseMutex.h"

namespace JeanUtility
{

	//
	// Forward declaration for friend.
	//
	class Cond;

	class CJeanThreadMutex : public CJeanBaseMutex
	{
	public:

		//
		// Lock & TryLock typedefs.
		//
		typedef LockT<CJeanThreadMutex> Lock;
		typedef TryLockT<CJeanThreadMutex> TryLock;

		inline CJeanThreadMutex();
		~CJeanThreadMutex();

		//
		// Note that lock/tryLock & unlock in general should not be used
		// directly. Instead use Lock & TryLock.
		//

		void lock() const;

		//
		// Returns true if the lock was acquired, and false otherwise.
		//
		bool tryLock() const;

		void unlock() const;

		//
		// Returns true if the mutex will unlock when calling unlock()
		// (false otherwise). For non-recursive mutexes, this will always
		// return true. 
		// This function is used by the Monitor implementation to know whether 
		// the Mutex has been locked for the first time, or unlocked for the 
		// last time (that is another thread is able to acquire the mutex).
		// Pre-condition: the mutex must be locked.
		//
		bool willUnlock() const;

	private:

		// noncopyable
		CJeanThreadMutex(const CJeanThreadMutex&);
		void operator=(const CJeanThreadMutex&);

		//
		// LockState and the lock/unlock variations are for use by the
		// Condition variable implementation.
		//
#ifdef JEAN_WIN32
		struct LockState
		{
		};
#endif

		void unlock(LockState&) const;
		void lock(LockState&) const;

		friend class Cond;

#ifdef JEAN_WIN32
		mutable CRITICAL_SECTION _mutex;
#endif
	};

	//
	// For performance reasons the following functions are inlined.
	//

#ifdef JEAN_WIN32

	inline
		CJeanThreadMutex::CJeanThreadMutex()
	{
		InitializeCriticalSection(&_mutex);
	}

	inline
		CJeanThreadMutex::~CJeanThreadMutex()
	{
		DeleteCriticalSection(&_mutex);
	}

	inline void
		CJeanThreadMutex::lock() const
	{
		EnterCriticalSection(&_mutex);
		assert(_mutex.RecursionCount == 1);
	}

	inline bool
		CJeanThreadMutex::tryLock() const
	{
		if(!TryEnterCriticalSection(&_mutex))
		{
			return false;
		}
		if(_mutex.RecursionCount > 1)
		{
			LeaveCriticalSection(&_mutex);
			assert(false);
		}
		return true;
	}

	inline void
		CJeanThreadMutex::unlock() const
	{
		assert(_mutex.RecursionCount == 1);
		LeaveCriticalSection(&_mutex);
	}

	inline void
		CJeanThreadMutex::unlock(LockState&) const
	{
		LeaveCriticalSection(&_mutex);
	}

	inline void
		CJeanThreadMutex::lock(LockState&) const
	{
		EnterCriticalSection(&_mutex);
	}

#endif    

	inline bool
		CJeanThreadMutex::willUnlock() const
	{
		return true;
	}

} // End namespace JeanUtility

#endif //__KFUTILITY_THREADMUTEX_H__
