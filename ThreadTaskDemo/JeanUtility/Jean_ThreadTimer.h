#pragma once
#ifndef __JEAN_THREADTIMER_H__
#define __JEAN_THREADTIMER_H__

#include "Jean_Time.h"
#include "Jean_SmartPtr.h"

namespace JeanUtility
{
	class CJeanThreadTaskTimer;
	class CJeanThreadTimer : public CJeanSharedObject
	{
		friend class CJeanTaskTimerThread;
	public:
		CJeanThreadTimer(const CJeanTime& interval, const bool bLoop = true, const CJeanTime delay = CJeanTime())
			:m_delay(delay)
			,m_interval(interval)
			,m_bLoop(bLoop)
			,m_bTerminate(false)
			,m_bDelayed(false)
		{
			m_elapse.reset();
		}
		void resume() { m_elapse.reset(); };
		void terminate() { m_bTerminate = true; };
		virtual void timeout() { return; };
	protected:
		void set_interval(const CJeanTime& interval) { m_interval = interval; };

	private:		
		void inc_elapse(const CJeanTime& elapse) { m_elapse += elapse; };
		bool is_terminate() const { return m_bTerminate; };
		bool is_loop() const { return m_bLoop; };
		bool is_delayed() const { return m_bDelayed; }
		void set_delayed(bool bDelay) { m_bDelayed = bDelay; }
		CJeanTime get_delay(){ return m_delay; };
		CJeanTime get_interval() { return m_interval; };
		CJeanTime get_elapse() { return m_elapse; };		

	private:
		CJeanTime m_delay;
		CJeanTime m_interval;
		CJeanTime m_elapse;
		const bool m_bLoop;	/**< 定时器循环 */
		bool m_bTerminate;	/**< 定时器终止 */  
		bool m_bDelayed;//delay超时是否已经发生过
	};

	typedef SmartPtr<CJeanThreadTimer> JeanTimerPtr;

} //namespace JeanUtility


#endif /* __JEAN_THREADTIMER_H__ */
