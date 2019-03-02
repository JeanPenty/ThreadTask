#include "StdAfx.h"
#include "LoginModule.h"

#include "LoginTask.h"

CLoginModule::CLoginModule(void)
{
	m_bInit = false;
}

CLoginModule::~CLoginModule(void)
{
}

bool CLoginModule::init()
{
	if (m_bInit) return true;

	try
	{
		m_bInit = true;
		start();
		return true;
	}
	catch(...)
	{
		uninit();
	}

	return false;
}

bool CLoginModule::uninit()
{
	if (!m_bInit) return true;

	m_bInit = false;

	try
	{
		//设置线程退出前的清理任务
		//TODO:
		terminate();
	}
	catch(...)
	{
		//
	}

	return false;
}

//线程任务处理
bool CLoginModule::process(JeanUtility::TaskExPtr& task)
{
	if (NULL == task) return false;

	switch(task->taskType_)
	{
	case TASK_LOGIN_TEST:
		HandleTestTask(task);
		break;
	default:
		break;
	}

	return true;
}

void CLoginModule::PostTestTask(const std::string& strParam)
{
	ns_logintask::TestTaskPtr taskPtr(new ns_logintask::TestTask);
	taskPtr->m_strParams = strParam;
	add_task(taskPtr);
}

void CLoginModule::HandleTestTask(JeanUtility::TaskExPtr &task)
{
	ns_logintask::TestTaskPtr myTask = 
		ns_logintask::TestTaskPtr::__dynamic_cast(task);
	if (NULL != myTask)
	{
		std::string strParams = myTask->m_strParams;
		int i = 0;
	}
}