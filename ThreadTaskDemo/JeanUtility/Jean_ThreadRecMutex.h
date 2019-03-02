#pragma once
#ifndef __JEAN_THREADRECMUTEX_H__
#define __JEAN_THREADRECMUTEX_H__

#include "Jean_Base.h"
#include "Jean_Lock.h"
#include "Jean_BaseMutex.h"

namespace JeanUtility
{

	//
	// Forward declarations for friend.
	//
	class Cond;

	//
	// Recursive Mutex implementation.
	//
	class CJeanThreadRecMutex : public CJeanBaseMutex
	{
	public:

		//
		// Lock & TryLock typedefs.
		//
		typedef LockT<CJeanThreadRecMutex> Lock;
		typedef TryLockT<CJeanThreadRecMutex> TryLock;

		CJeanThreadRecMutex(){
			_count = 0;
			InitializeCriticalSection(&_mutex);
		}
		~CJeanThreadRecMutex(){
			assert(_count == 0);
			DeleteCriticalSection(&_mutex);
		}

		//
		// Note that lock/tryLock & unlock in general should not be used
		// directly. Instead use Lock & TryLock.
		//

		void lock() const;

		//
		// Returns true if the lock was acquired or was already acquired
		// by the calling thread, and false otherwise.
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
		CJeanThreadRecMutex(const CJeanThreadRecMutex&);
		void operator=(const CJeanThreadRecMutex&);

		//
		// LockState and the lock/unlock variations are for use by the
		// Condition variable implementation.
		//
#ifdef JEAN_WIN32
		struct LockState
		{
			int count;
		};
#endif

		void unlock(LockState&) const;
		void lock(LockState&) const;

		friend class Cond;

#ifdef JEAN_WIN32
		mutable CRITICAL_SECTION _mutex;
#endif    

		mutable int _count;
	};

} // End namespace JeanUtility

#endif //__JEAN_THREADRECMUTEX_H__
