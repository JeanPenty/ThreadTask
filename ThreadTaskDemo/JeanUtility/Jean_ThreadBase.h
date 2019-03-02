/*
* �ļ����ƣ�Jean_ThreadBase.h
* �ļ���ʶ��
* ժ����Ҫ����װ���̻߳���
* ��    �ܣ��Բ���ϵͳ�̵߳ķ�װ
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

		//�ȴ��߳��˳���join�ڲ������detach
		void join();

		//������̵߳Ŀ���Ȩ
		void detach();

		static void sleep(const CJeanTime&);
		static void yield();

	public:
		DWORD getThreadId() const ;
		bool isAlive() const ;
		void	_done();

	protected:
		//�߳�ִ�к���
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

