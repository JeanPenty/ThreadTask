#pragma once
#ifndef __JEAN_TASK_H__
#define __JEAN_TASK_H__

#include "Jean_SmartPtr.h"

namespace JeanUtility
{
	class CTaskBase : public CJeanSharedObject
	{
	public:
		CTaskBase() {}
		virtual ~CTaskBase() {}

	public:
		virtual int foo() = 0;

	private:
		/* not allow copying and assignment. */
		CTaskBase(const CTaskBase &);
		void operator= (const CTaskBase &);
	};
	typedef SmartPtr<CTaskBase> TaskBasePtr;

	class CTaskEx : virtual public CTaskBase
	{
	public:
		CTaskEx()
			: taskType_(0), result_(0)
		{
		}
		virtual ~CTaskEx() {}

	public:
		virtual int foo() { return 0; }

	public:
		int taskType_;		/**< 标识 */
		int result_;		/**< 结果 */
	};
	typedef SmartPtr<CTaskEx> TaskExPtr;
}

#endif //__JEAN_TASK_H__
