#pragma once
#ifndef __JEAN_SMARTPTR_H__
#define __JEAN_SMARTPTR_H__

#if defined(JEAN_WIN32)
#include <windows.h>
#endif
#include "Jean_ThreadMutex.h"


//
// Base classes for reference counted types. The SmartPtr template
// can be used for smart pointers to types derived from these bases.
//
// SharedObject
// ===============
//
// A thread-safe base class for reference-counted types.
//
namespace JeanUtility
{
	class CJeanSharedObject
	{
	public:
		CJeanSharedObject() : m_lRefCount(0)
		{
		}

		virtual ~CJeanSharedObject()
		{
		}

		void __incRef()
		{
#if defined(JEAN_WIN32)
			assert(InterlockedExchangeAdd(const_cast<long *>(&(this->m_lRefCount)), 0) >= 0);
			::InterlockedIncrement(const_cast<long *>(&(this->m_lRefCount)));
#endif
		}

		void __decRef()
		{
#if defined(JEAN_WIN32)
			assert(InterlockedExchangeAdd(const_cast<long *>(&(this->m_lRefCount)), 0) > 0);
			long value = ::InterlockedDecrement(const_cast<long *>(&(this->m_lRefCount)));
#endif
			if (0 == value )
			{
				recycle();
			}
		}

		int __getRef()
		{
#if defined(JEAN_WIN32)
			return ::InterlockedExchangeAdd(const_cast<long *>(&(this->m_lRefCount)), 0);
#endif
		}
	protected:
		virtual void recycle()
		{
			delete this;
		}

	private:
		volatile long m_lRefCount;
	};

	//
	// "smart pointer" class for classes derived from SharedObject.
	//
	template<typename T_Class, typename endclass = CJeanSharedObject, typename T_Lock = CJeanThreadMutex>
	class SmartPtr
	{
	public:
		explicit SmartPtr(T_Class* handler = 0)
		{
			if (handler)
			{
				handler->endclass::__incRef();
			}
			this->handler_ = handler;
		}

		SmartPtr(const SmartPtr& right)
		{
			this->handler_ = (const_cast<SmartPtr&>(right)).__lock_incRef();
		}

		template<typename Y>
		SmartPtr(const SmartPtr<Y>& right)
		{
			this->handler_ = (const_cast<SmartPtr<Y>&>(right)).__lock_incRef();
		}

		SmartPtr& operator=(T_Class* right_ptr)
		{	
			// assign compatible right (assume pointer)
			if (this->handler_ != right_ptr)
			{
				if (right_ptr)
				{
					right_ptr->endclass::__incRef();
				}

				{
					typename T_Lock::Lock guard(lock_);

					T_Class* ptr = this->handler_;
					this->handler_ = right_ptr;

					if (ptr)
					{
						ptr->endclass::__decRef();
					}
				}

			}
			return (*this);
		}

		SmartPtr& operator=(const SmartPtr& right)
		{
			// assign compatible right (assume pointer)
			if (this->handler_ != right.handler_)
			{
				T_Class* right_ptr = (const_cast<SmartPtr&>(right)).__lock_incRef();

				{
					typename T_Lock::Lock guard(lock_);

					T_Class* ptr = this->handler_;
					this->handler_ = right_ptr;

					if (ptr)
					{
						ptr->endclass::__decRef();
					}
				}

			}
			return (*this);
		}

		template<typename Y>
		SmartPtr& operator=(const SmartPtr<Y>& right)
		{
			if(this->handler_ != right.handler_)
			{
				T_Class* right_ptr = (const_cast<SmartPtr<Y>&>(right)).__lock_incRef();

				{
					typename T_Lock::Lock guard(lock_);

					T_Class* ptr = this->handler_;
					this->handler_ = right_ptr;

					if(ptr)
					{
						ptr->endclass::__decRef();
					}
				}

			}
			return *this;
		}

		~SmartPtr()
		{
			if (this->handler_)
				this->handler_->endclass::__decRef();
		}

		bool empty() const
		{
			return (this->handler_ == 0);
		}

		bool operator==(const SmartPtr& right) const
		{
			return (this->handler_ == right.handler_);
		}
		bool operator!=(const SmartPtr& right) const
		{
			return (this->handler_ != right.handler_);
		}
		bool operator==(T_Class* right) const
		{
			return (this->handler_ == right);
		}
		bool operator!=(T_Class* right) const
		{
			return (this->handler_ != right);
		}
		T_Class *operator->() const
		{
			return this->handler_;
		}
		T_Class& operator*() const
		{
			return (*(this->handler_));
		}
		T_Class* get() const
		{
			return this->handler_;
		}
		operator T_Class*() const
		{
			return this->handler_;
		}

		template<typename Y>
		static SmartPtr __dynamic_cast(const SmartPtr<Y>& right)
		{
			return SmartPtr(dynamic_cast<T_Class* const>(right.handler_));
		}

		template<typename Y>
		static SmartPtr __dynamic_cast(Y* right_ptr)
		{
			return SmartPtr(dynamic_cast<T_Class*>(right_ptr));
		}

		// dynamic cast need handler_ and __incRef is public
	public:
		T_Class* __lock_incRef() 
		{
			typename T_Lock::Lock guard(lock_);

			if (this->handler_)
			{
				this->handler_->endclass::__incRef();
			}

			return this->handler_;
		}

		T_Class* handler_;

	private:
		T_Lock lock_;
	};
}

#endif //__JEAN_SMARTPTR_H__
