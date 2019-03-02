#pragma once
#ifndef __JEAN_SINGLETON_H__
#define __JEAN_SINGLETON_H__

#include "Jean_ThreadMutex.h"
#include "Jean_SmartPtr.h"

namespace JeanUtility
{
	//Singleton
	template<typename T>
	class Singleton
	{
	public:
		static inline T* instance()
		{
			if (0 == m_sInstance)
			{
				CJeanThreadMutex::Lock guard(m_sMutex);
				if (0 == m_sInstance)
				{
					m_sInstance = new T;
				}
			}
			return m_sInstance;
		}

		static inline void free()
		{
			if (m_sInstance != 0)
			{
				CKfThreadMutex::Lock guard(m_sMutex);
				if(m_sInstance != 0)
				{
					delete m_sInstance;
					m_sInstance = 0;
				}				
			}
		}

	protected:
		Singleton() {}
		virtual ~Singleton(){}
	private:
		Singleton(const Singleton&) {}
		Singleton& operator=(const Singleton&) {}

	private:
		static T* m_sInstance;
		static CJeanThreadMutex m_sMutex;
	};

	template<typename T>
	T* Singleton<T>::m_sInstance = 0;

	template<typename T>
	CJeanThreadMutex Singleton<T>::m_sMutex;


	//SmartSingleton
	template<typename T>
	class SmartSingleton
	{
	public:
		static inline SmartPtr<T>& instance()
		{
			if (m_sInstance.get() == 0)
			{
				CJeanThreadMutex::Lock guard(m_sMutex);

				if (m_sInstance.get() == 0)
				{
					m_sInstance = new T;
				}
			}
			return m_sInstance;
		}

		static inline void free()
		{
			if(m_sInstance.get() != 0)
			{
				CJeanThreadMutex::Lock guard(m_sMutex);

				if (m_sInstance.get() != 0)
				{
					m_sInstance = 0;
				}
			}
		}

	protected:
		SmartSingleton() {}
		virtual ~SmartSingleton()
		{
			// Don't free again
		}
	private:
		SmartSingleton(const SmartSingleton&) {}
		SmartSingleton& operator=(const SmartSingleton&) {}

	private:
		static SmartPtr<T> m_sInstance;
		static CJeanThreadMutex m_sMutex;
	};

	template<typename T>
	SmartPtr<T> SmartSingleton<T>::m_sInstance = 0;

	template<typename T>
	CJeanThreadMutex SmartSingleton<T>::m_sMutex;

} //namespace JeanUtility

#endif //__JEAN_SINGLETON_H__
