#include "stdafx.h"
#include "Jean_TaskTimerThread.h"

namespace JeanUtility
{
	CJeanTaskTimerThread::CJeanTaskTimerThread(const std::string sThreadName, int nMaxLen)
		:m_sThreadName(sThreadName), m_nMaxLen(nMaxLen)
	{
		terminated_ = false;
		timeout_ = JeanUtility::CJeanTime::milliSeconds(10);
		exit_task_ = NULL;
	};

	CJeanTaskTimerThread::~CJeanTaskTimerThread()
	{
		vt_new_timer_.clear();
		list_timer_.clear();
	};

	void CJeanTaskTimerThread::terminate()
	{
		terminated_ = true;
		MonitorT<JeanUtility::CJeanThreadMutex>::Lock guard(monitor_);
		monitor_.notify();
	};

	int CJeanTaskTimerThread::add_task(const JeanUtility::TaskBasePtr& task)
	{
		MonitorT<JeanUtility::CJeanThreadMutex>::Lock guard(monitor_);

		int size = deque_task_.size();
		if ( size >= m_nMaxLen)
		{
			return  size;
		}

		if (deque_task_.empty())
			monitor_.notify();
		deque_task_.push_back(task);
		size = deque_task_.size();
		return size;
	};

	int CJeanTaskTimerThread::set_exit_task(const JeanUtility::TaskBasePtr& task)
	{
		exit_task_ = task;
		return 0;
	}

	int CJeanTaskTimerThread::get_task_size()
	{
		MonitorT<JeanUtility::CJeanThreadMutex>::Lock guard(monitor_);
		int size = deque_task_.size();

		return size;
	}

	void CJeanTaskTimerThread::create_timer(const JeanUtility::JeanTimerPtr& timer)
	{
		JeanUtility::CJeanThreadMutex::Lock guard(lock_new_timer_);
		vt_new_timer_.push_back(timer);
	};

	void CJeanTaskTimerThread::destory_timer(const JeanUtility::JeanTimerPtr& timer)
	{
		JeanUtility::CJeanThreadMutex::Lock guard(lock_del_timer_);
		vt_del_timer_.push_back(timer);
	};

	void CJeanTaskTimerThread::run()
	{
		now_ = JeanUtility::CJeanTime::now();
		timestamp_ = now_;

		TaskBasePtr task;

		while (!terminated_)
		{
			beforeProcessTask();

			{
				/* 注意Lock的作用范围，防止重复加锁 */
				MonitorT<JeanUtility::CJeanThreadMutex>::Lock guard(monitor_);
				if (deque_task_.empty())
				{
					monitor_.timedWait(timeout_);
				}

				now_ = JeanUtility::CJeanTime::now();
				if (!deque_task_.empty())
				{
					task = deque_task_.front();
					deque_task_.pop_front();
				}
			}

			if (terminated_)
				break;

			if (task != NULL)
			{
				try
				{
					JeanUtility::TaskExPtr taskEx =JeanUtility:: TaskExPtr::__dynamic_cast(task);
					if (taskEx != NULL)
					{
						process(taskEx);
					}
					else
					{
						task->foo();
					}
				}
				catch (...)
				{
				}
				task = NULL;
			}

			afterProcessTask();

			try
			{
				ProcessTimer();
			}
			catch (...)
			{
			}
		}

		if (exit_task_ != NULL)
		{
			try
			{
				JeanUtility::TaskExPtr taskEx = JeanUtility::TaskExPtr::__dynamic_cast(exit_task_);
				if (taskEx != NULL)
				{
					process(taskEx);
				}
				else
				{
					exit_task_->foo();
				}
			}
			catch (...)
			{
			}
			exit_task_ = NULL;
		}

	};

	bool CJeanTaskTimerThread::ProcessTimer()
	{
		if (now_ <= timestamp_)
		{
			timestamp_ = now_;
			return false;
		}

		if (!vt_new_timer_.empty())
		{
			JeanUtility::CJeanThreadMutex::Lock guard(lock_new_timer_);

			for (std::vector<JeanTimerPtr>::iterator it = vt_new_timer_.begin(); it != vt_new_timer_.end(); ++it)
			{
				if((*it) != NULL)
				{
					list_timer_.push_back(*it);
				}
			}
			vt_new_timer_.clear();
		}

		if (!vt_del_timer_.empty())
		{
			JeanUtility::CJeanThreadMutex::Lock guard(lock_del_timer_);

			for (std::vector<JeanTimerPtr>::iterator it = vt_del_timer_.begin(); it != vt_del_timer_.end(); ++it)
			{
				list_timer_.remove(*it);
			}
			vt_del_timer_.clear();
		}

		now_ =JeanUtility:: CJeanTime::now();

		for (std::list<JeanUtility::JeanTimerPtr>::iterator it = list_timer_.begin(); it != list_timer_.end(); ++it)
		{
			if (NULL != (*it))
			{
				if ((*it)->is_terminate())
				{
					destory_timer(*it);
					continue;
				}
				(*it)->inc_elapse(now_- timestamp_);
				CJeanTime realInterval = (*it)->is_delayed()? (*it)->get_interval() : (*it)->get_delay();
				if ((*it)->get_elapse() >= realInterval)
				{
					(*it)->timeout();
					if(false == (*it)->is_delayed())
					{
						(*it)->set_delayed(true);
					}
					if ((*it)->is_loop())
					{
						(*it)->resume();
					}
					else
					{
						(*it)->terminate();
					}
				}
			}
		}
		timestamp_ = now_;

		return true;
	};

}// namespace JeanUtility