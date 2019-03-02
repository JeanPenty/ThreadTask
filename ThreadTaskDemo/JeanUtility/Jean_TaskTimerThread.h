#pragma once
#ifndef __JEAN_TASKTIMERTHREAD_H__
#define __JEAN_TASKTIMERTHREAD_H__

#include "Jean_ThreadBase.h"
#include "Jean_ThreadTimer.h"
#include "Jean_Monitor.h"
#include "Jean_ThreadMutex.h"
#include "Jean_SmartPtr.h"
#include "Jean_Task.h"

namespace JeanUtility
{
	class CJeanTaskTimerThread : public JeanUtility::CJeanThreadBase
	{
	public:
		CJeanTaskTimerThread(const std::string sThreadName ="Thread", int nMaxLen = 1024);
		virtual ~CJeanTaskTimerThread();

		void terminate();

		int add_task(const JeanUtility::TaskBasePtr& task);

		int set_exit_task(const JeanUtility::TaskBasePtr& task);

		int get_task_size();

		void create_timer(const JeanUtility::JeanTimerPtr& timer);

		void destory_timer(const JeanUtility::JeanTimerPtr& timer);

		virtual bool process(JeanUtility::TaskExPtr& task) { return false; };

	protected:
		virtual void run();

		//每处理一个任务（结束任务除外）之前调用
		virtual void beforeProcessTask() {};
		//每处理一个任务（结束任务除外）之后调用
		virtual void afterProcessTask(){};

	private:
		bool ProcessTimer();

	private:
		bool terminated_;
		JeanUtility::CJeanTime timeout_;
		JeanUtility::CJeanTime now_;
		JeanUtility::CJeanTime timestamp_;

		MonitorT<JeanUtility::CJeanThreadMutex> monitor_;
		std::deque<JeanUtility::TaskBasePtr> deque_task_;
		std::list<JeanUtility::JeanTimerPtr> list_timer_;

		JeanUtility::CJeanThreadMutex lock_new_timer_;
		JeanUtility::CJeanThreadMutex lock_del_timer_;
		std::vector<JeanUtility::JeanTimerPtr> vt_new_timer_;
		std::vector<JeanUtility::JeanTimerPtr> vt_del_timer_;

		std::string m_sThreadName;
		int m_nMaxLen;

		//结束任务，用于线程结束时清理线程本身分配的未加锁资源
		TaskBasePtr  exit_task_;
	};
}


#endif //__JEAN_TASKTIMERTHREAD_H__
