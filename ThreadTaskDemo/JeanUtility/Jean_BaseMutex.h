#pragma once
#ifndef __JEAN_BASEMUTEX_H__
#define __JEAN_BASEMUTEX_H__

#include "Jean_Base.h"
#include "Jean_Lock.h"

namespace JeanUtility
{

	class CJeanBaseMutex
	{
	public:

		typedef LockT<CJeanBaseMutex> Lock;
		typedef TryLockT<CJeanBaseMutex> TryLock;

		CJeanBaseMutex(){};
		virtual ~CJeanBaseMutex(){};

		virtual void lock() const = 0;

		virtual bool tryLock() const = 0;

		virtual void unlock() const = 0;

	private:

		// noncopyable
		CJeanBaseMutex(const CJeanBaseMutex&);
		void operator=(const CJeanBaseMutex&);
	};

	class CJeanNullMutex : public CJeanBaseMutex
	{
	public:

		typedef LockT<CJeanNullMutex> Lock;
		typedef TryLockT<CJeanNullMutex> TryLock;

		CJeanNullMutex(){};
		~CJeanNullMutex(){};

		void lock() const {};

		bool tryLock() const { return true; };

		void unlock() const {};

	private:

		// noncopyable
		CJeanNullMutex(const CJeanNullMutex&);
		void operator=(const CJeanNullMutex&);
	};

} // End namespace JeanUtility

#endif //__JEAN_BASEMUTEX_H__
