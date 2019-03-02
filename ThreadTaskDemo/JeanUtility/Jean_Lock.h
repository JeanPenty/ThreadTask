#pragma once
#ifndef __JEAN_LOCK_H__
#define __JEAN_LOCK_H__

#include "Jean_Base.h"

namespace JeanUtility
{

	//
	// Forward declarations.
	//
	class Cond;

	// LockT and TryLockT are the preferred construct to lock/tryLock/unlock
	// simple and recursive mutexes. You typically allocate them on the
	// stack to hold a lock on a mutex.
	// LockT and TryLockT are not recursive: you cannot acquire several times 
	// in a row a lock with the same Lock or TryLock object.
	// 
	// We must name this LockT instead of Lock, because otherwise some
	// compilers (such as Sun C++ 5.4) have problems with constructs
	// such as:
	//
	// class Foo
	// {
	//     // ...
	//     typedef Lock<Mutex> Lock;
	// }
	//
	template <typename T>
	class LockT
	{
	public:

		LockT(const T& mutex) :
		  _mutex(mutex)
		  {
			  _mutex.lock();
			  _acquired = true;
		  }

		  ~LockT()
		  {
			  if (_acquired)
			  {
				  _mutex.unlock();
			  }
		  }

		  void acquire() const
		  {
			  if (_acquired)
			  {
				  assert(false);
			  }
			  _mutex.lock();
			  _acquired = true;
		  }


		  bool tryAcquire() const
		  {
			  if (_acquired)
			  {
				  assert(false);
			  }
			  _acquired = _mutex.tryLock();
			  return _acquired;
		  }

		  void release() const
		  {
			  if (!_acquired)
			  {
				  assert(false);
			  }
			  _mutex.unlock();
			  _acquired = false;
		  }

		  bool acquired() const
		  {
			  return _acquired;
		  }

	protected:

		// TryLockT's contructor
		LockT(const T& mutex, bool) :
			 _mutex(mutex)
			 {
				 _acquired = _mutex.tryLock();
			 }

	private:

		// Not implemented; prevents accidental use.
		//
		LockT(const LockT&);
		LockT& operator=(const LockT&);

		const T& _mutex;
		mutable bool _acquired;

		friend class Cond;
	};

	//
	// Must be named TryLockT, not TryLock. See the comment for LockT for
	// an explanation.
	//
	template <typename T>
	class TryLockT : public LockT<T>
	{
	public:

		TryLockT(const T& mutex) :
		  LockT<T>(mutex, true)
		  {}
	};

	template<typename T>
	class LockPtrT
	{
	public:
		LockPtrT(T* pMutex):m_pMutex(pMutex)
		{
			if(m_pMutex)
			{
				m_pMutex->lock();
			}
		}

		~LockPtrT()
		{
			if(m_pMutex)
			{
				m_pMutex->unlock();
			}
		}
	private:

		LockPtrT(const LockPtrT&);
		LockPtrT& operator=(const LockPtrT&);

	private:
		T* m_pMutex;
	};

} // End namespace JeanUtility

#endif //__JEAN_LOCK_H__
