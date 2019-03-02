#ifndef __LOGINTASK_H__
#define __LOGINTASK_H__

#pragma once

#define TASK_LOGIN_TEST		1

namespace ns_logintask
{
	class TestTask : public JeanUtility::CTaskEx
	{
	public:
		TestTask(){
			taskType_ = TASK_LOGIN_TEST;
		}

		//自定义数据
		std::string m_strParams;
	};
	typedef JeanUtility::SmartPtr<TestTask> TestTaskPtr;
}
#endif