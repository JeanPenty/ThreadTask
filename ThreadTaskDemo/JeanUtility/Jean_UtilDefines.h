//基本运算工具定义
#pragma once
#ifndef __JEAN_UTILDEFINES_H__
#define __JEAN_UTILDEFINES_H__

#include "Jean_Platform.h"

#ifdef JEAN_WIN32

/* 设定select等函数最大处理句柄数为2048 - 原64 */
#ifdef FD_SETSIZE
	#undef FD_SETSIZE
#endif	// FD_SETSIZE

	/*
	* VC6中, windwos.h会include winsock.h, winsock.h会
	* 定义FD_SETSIZE, 所以, 必须在include windows.h
	* 定义FD_SETSIZE
	*/
	#define FD_SETSIZE 2048L

	/* 编译器为VC6时, include windows.h */
	#if ( _MSC_VER == 1200 )
		#include <windows.h>
	#endif	// ( _MSC_VER == 1200 )

	#include <winsock2.h>
	#include <Ws2tcpip.h>
	#include <windows.h>
#endif	// KF_WIN32

#ifdef JEAN_WIN32
	#include <string.h>
	#include <direct.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <limits.h>
	#include <stddef.h>
	#include <stdarg.h>
	#include <signal.h>
	#include <errno.h>
	#include <tchar.h>

	#include <crtdbg.h>
	#include <process.h>
#endif


#include <fcntl.h>
#include <memory>
#include <utility>
#include <algorithm>
#include <utility>
#include <set> 
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>

/*
 * 分隔符定义
 */
#ifdef JEAN_WIN32
	#define JEAN_OS_SEPARATE '\\'
#endif	// JEAN_WIN32

/* 检查某bit有没有被设置 */
#ifndef JEAN_BIT_ENABLED
	#define JEAN_BIT_ENABLED( dword, bit ) ( ((dword) & (bit)) != 0 )
#endif	// JEAN_BIT_ENABLED

/* 检查某bit有没有被屏蔽 */
#ifndef JEAN_BIT_DISABLED
	#define JEAN_BIT_DISABLED( dword, bit ) ( ((dword) & (bit)) == 0 )
#endif	// JEAN_BIT_DISABLED

/* 检查某bit的值是否与<mask>相等 */
#ifndef JEAN_BIT_CMP_MASK
	#define JEAN_BIT_CMP_MASK( dword, bit, mask ) ( ((dword) & (bit)) == mask )
#endif	// JEAN_BIT_CMP_MASK

/* 设置某bit */
#ifndef JEAN_SET_BITS
	#define JEAN_SET_BITS( dword, bits ) ( dword |= (bits) )
#endif	// JEAN_SET_BITS

/* 屏蔽某bit */
#ifndef JEAN_CLR_BITS
	#define JEAN_CLR_BITS( dword, bits ) ( dword &= ~(bits) )
#endif	// JEAN_CLR_BITS

/* 删除一个指针并置为NULL */
#ifndef JEAN_DELETE
	#define JEAN_DELETE( p )			\
	do								\
	{								\
		if ( NULL != (p) )			\
		{							\
			delete (p);				\
			(p) = NULL;				\
		}							\
	} while ( 0 )
#endif	// JEAN_DELETE

/* 删除一个指针数组并置为NULL */
#ifndef JEAN_ARRAY_DELETE
	#define JEAN_ARRAY_DELETE( pArray )	\
	do									\
	{									\
		if ( NULL != (pArray) )			\
		{								\
			delete[] (pArray);			\
			(pArray) = NULL;				\
		}								\
	} while( 0 )
#endif	// JEAN_ARRAY_DELETE

/* 填充<length>个'0' */
#define JEAN_ZERO( psz, length ) memset( psz, 0, length )

#endif	// __JEAN_UTILDEFINES_H__

