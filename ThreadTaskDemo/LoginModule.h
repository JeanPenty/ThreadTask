#pragma once

class CLoginModule : public JeanUtility::CJeanTaskTimerThread
	, public JeanUtility::Singleton<CLoginModule>
{
public:
	CLoginModule(void);
	~CLoginModule(void);

public:
	bool init();
	bool uninit();

	virtual bool process(JeanUtility::TaskExPtr& task);
	void OnThreadExit(){}

	virtual void beforeProcessTask(){}
	virtual void afterProcessTask(){}

public:
	//线程添加任务示例
	void PostTestTask(const std::string& strParam);

private:
	//线程任务处理示例
	void HandleTestTask(JeanUtility::TaskExPtr &task);

private:
	bool m_bInit;
};
