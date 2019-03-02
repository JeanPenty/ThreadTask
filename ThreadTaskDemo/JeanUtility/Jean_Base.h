#pragma once
#ifndef __JEAN_BASE_H__
#define __JEAN_BASE_H__

#include "Jean_Platform.h"
#include "Jean_UtilDefines.h"
#include "Jean_TypeDefines.h"
#include "Jean_ErrorDefines.h"

namespace JeanUtility
{

	class noncopyable
	{
	protected:

		noncopyable() { }
		~noncopyable() { } // May not be virtual! Classes without virtual 
		// operations also derive from noncopyable.

	private:

		noncopyable(const noncopyable&);
		const noncopyable& operator=(const noncopyable&);
	};

}

#endif //__JEAN_BASE_H__
