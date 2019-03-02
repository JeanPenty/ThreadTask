/*
* 文件名称：Jean_ThreadBase.h
* 文件标识：
* 摘　　要：封装的线程基类
* 功    能：对操作系统线程的封装
*/

#pragma once
#ifndef	__JEAN_THREADBASE_H__
#define	__JEAN_THREADBASE_H__

#include "Jean_Base.h"
#include "Jean_ThreadMutex.h"
#include "Jean_Time.h"
#include "Jean_SmartPtr.h"
namespace JeanUtility
{
	class CJeanThreadBase : public CJeanSharedObject
	{
	public:
		CJeanThreadBase();
		virtual ~CJeanThreadBase();

		virtual bool start(size_t stackSize = 0);

		//等待线程退出，join内部会调用detach
		void join();

		//解除对线程的控制权
		void detach();

		static void sleep(const CJeanTime&);
		static void yield();

	public:
		DWORD getThreadId() const ;
		bool isAlive() const ;
		void	_done();

	protected:
		//线程执行函数
		virtual void run() = 0;
	private:
		CJeanThreadBase(const CJeanThreadBase &);
		CJeanThreadBase & operator=(const CJeanThreadBase &);

		static unsigned int __stdcall threadFunc(void * arg);

	protected:
		CJeanThreadMutex  m_mtxState;

		bool				m_bStarted;
		bool				m_bRunning;

		HANDLE			m_hThread;
		DWORD			m_dwThreadID;
	};

	typedef SmartPtr<CJeanThreadBase> JeanThreadBasePtr;
}

#endif //__JEAN_THREADBASE_H__

