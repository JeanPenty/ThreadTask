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
	//�߳��������ʾ��
	void PostTestTask(const std::string& strParam);

private:
	//�߳�������ʾ��
	void HandleTestTask(JeanUtility::TaskExPtr &task);

private:
	bool m_bInit;
};
