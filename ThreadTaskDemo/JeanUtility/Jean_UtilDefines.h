//�������㹤�߶���
#pragma once
#ifndef __JEAN_UTILDEFINES_H__
#define __JEAN_UTILDEFINES_H__

#include "Jean_Platform.h"

#ifdef JEAN_WIN32

/* �趨select�Ⱥ������������Ϊ2048 - ԭ64 */
#ifdef FD_SETSIZE
	#undef FD_SETSIZE
#endif	// FD_SETSIZE

	/*
	* VC6��, windwos.h��include winsock.h, winsock.h��
	* ����FD_SETSIZE, ����, ������include windows.h
	* ����FD_SETSIZE
	*/
	#define FD_SETSIZE 2048L

	/* ������ΪVC6ʱ, include windows.h */
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
 * �ָ�������
 */
#ifdef JEAN_WIN32
	#define JEAN_OS_SEPARATE '\\'
#endif	// JEAN_WIN32

/* ���ĳbit��û�б����� */
#ifndef JEAN_BIT_ENABLED
	#define JEAN_BIT_ENABLED( dword, bit ) ( ((dword) & (bit)) != 0 )
#endif	// JEAN_BIT_ENABLED

/* ���ĳbit��û�б����� */
#ifndef JEAN_BIT_DISABLED
	#define JEAN_BIT_DISABLED( dword, bit ) ( ((dword) & (bit)) == 0 )
#endif	// JEAN_BIT_DISABLED

/* ���ĳbit��ֵ�Ƿ���<mask>��� */
#ifndef JEAN_BIT_CMP_MASK
	#define JEAN_BIT_CMP_MASK( dword, bit, mask ) ( ((dword) & (bit)) == mask )
#endif	// JEAN_BIT_CMP_MASK

/* ����ĳbit */
#ifndef JEAN_SET_BITS
	#define JEAN_SET_BITS( dword, bits ) ( dword |= (bits) )
#endif	// JEAN_SET_BITS

/* ����ĳbit */
#ifndef JEAN_CLR_BITS
	#define JEAN_CLR_BITS( dword, bits ) ( dword &= ~(bits) )
#endif	// JEAN_CLR_BITS

/* ɾ��һ��ָ�벢��ΪNULL */
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

/* ɾ��һ��ָ�����鲢��ΪNULL */
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

/* ���<length>��'0' */
#define JEAN_ZERO( psz, length ) memset( psz, 0, length )

#endif	// __JEAN_UTILDEFINES_H__

