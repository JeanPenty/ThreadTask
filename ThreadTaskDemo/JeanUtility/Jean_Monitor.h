#pragma once
#ifndef __JEAN_MONITOR_H__
#define __JEAN_MONITOR_H__

#include "Jean_Base.h"
#include "Jean_Lock.h"
#include "Jean_Cond.h"

namespace JeanUtility
{
	//
	// This monitor implements the Mesa monitor semantics. That is any
	// calls to notify() or notifyAll() are delayed until the monitor is
	// unlocked.
	//
	template <class T>
	class MonitorT
	{
	public:

		typedef LockT<MonitorT<T> > Lock;
		typedef TryLockT<MonitorT<T> > TryLock;

		MonitorT();
		~MonitorT();

		//
		// Note that lock/tryLock & unlock in general should not be used
		// directly. Instead use Lock & TryLock.
		//
		void lock() const;
		void unlock() const;
		bool tryLock() const;

		void wait() const;
		bool timedWait(const JeanUtility::CJeanTime&) const;
		void notify();
		void notifyAll();

	private:

		// noncopyable
		MonitorT(const MonitorT&);
		void operator=(const MonitorT&);

		void notifyImpl(int) const;

		mutable Cond _cond;
		T _mutex;
		mutable int _nnotify;
	};
} // End namespace

//
// Since this monitor implements the Mesa monitor semantics calls to
// notify() or notifyAll() are delayed until the monitor is
// unlocked. This can happen either due to a call to unlock(), or a
// call to wait(). The _nnotify flag keeps track of the number of
// pending notification calls. -1 indicates a broadcast, a positive
// number indicates <n> calls to notify(). The _nnotify flag is reset
// upon initial acquisition of the monitor lock (either through a call
// to lock(), or a return from wait().
//

template <class T> inline
JeanUtility::MonitorT<T>::MonitorT() :
    _nnotify(0)
{
}

template <class T> inline
JeanUtility::MonitorT<T>::~MonitorT()
{
}

template <class T> inline void
JeanUtility::MonitorT<T>::lock() const
{
    _mutex.lock();
    if(_mutex.willUnlock())
    {
        //
        // On the first mutex acquisition reset the number pending
        // notifications.
        //
        _nnotify = 0;
    }
}

template <class T> inline void
JeanUtility::MonitorT<T>::unlock() const
{
    if(_mutex.willUnlock())
    {
        //
        // Perform any pending notifications.
        //
        notifyImpl(_nnotify);
    }
    _mutex.unlock();

/*
    int nnotify = _nnotify;
    if(_mutex.unlock())
    {
        //
        // Perform any pending notifications.
        //
        notifyImpl(nnotify);
    }
*/
}

template <class T> inline bool
JeanUtility::MonitorT<T>::tryLock() const
{
    bool result = _mutex.tryLock();
    if(result && _mutex.willUnlock())
    {
        //
        // On the first mutex acquisition reset the number pending
        // notifications.
        //
        _nnotify = 0;
    }
    return result;
}

template <class T> inline void
JeanUtility::MonitorT<T>::wait() const
{
    //
    // Perform any pending notifies
    //
    notifyImpl(_nnotify);

    //
    // Wait for a notification
    //
    try
    {
        _cond.waitImpl(_mutex);
        //
        // Reset the nnotify count once wait() returns.
        //
    }
    catch(...)
    {
        _nnotify = 0;
        throw;
    }

    _nnotify = 0;
}

template <class T> inline bool
JeanUtility::MonitorT<T>::timedWait(const JeanUtility::CJeanTime& timeout) const
{
    //
    // Perform any pending notifies.
    //
    notifyImpl(_nnotify);

    bool rc;
    //
    // Wait for a notification.
    //
    try
    {
        rc = _cond.timedWaitImpl(_mutex, timeout);

        //
        // Reset the nnotify count once wait() returns.
        //
    }
    catch(...)
    {
        _nnotify = 0;
        throw;
    }

    _nnotify = 0;
    return rc;
}

template <class T> inline void
JeanUtility::MonitorT<T>::notify()
{
    //
    // Increment the _nnotify flag, unless a broadcast has already
    // been requested.
    //
    if(_nnotify != -1)
    {
        ++_nnotify;
    }
}

template <class T> inline void
JeanUtility::MonitorT<T>::notifyAll()
{
    //
    // -1 (indicates broadcast)
    //
    _nnotify = -1;
}


template <class T> inline void
JeanUtility::MonitorT<T>::notifyImpl(int nnotify) const
{
    //
    // Zero indicates no notifies.
    //
    if(nnotify != 0)
    {
        //
        // -1 means notifyAll.
        //
        if(nnotify == -1)
        {
            _cond.broadcast();
            return;
        }
        else
        {
            //
            // Otherwise notify n times.
            //
            while(nnotify > 0)
            {
                _cond.signal();
                --nnotify;
            }
        }
    }
}

#endif //__JEAN_MONITOR_H__
