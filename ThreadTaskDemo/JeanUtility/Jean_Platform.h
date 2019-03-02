//平台相关(包括操作系统和编译器)基本定义文件

#pragma once
#ifndef __JEAN_PLATFORM_H__
#define __JEAN_PLATFORM_H__

/*
 *	检测操作系统
 */

/* windows系统 */
#if defined(_WIN32) || defined (_WIN64)
#ifndef JEAN_WIN32
#define JEAN_WIN32
#endif	// JEAN_WIN32
#endif	// WIN32


/*
 *	只支持win32和linux
 */
#if (!defined(JEAN_WIN32))
#error ONLY support windows
#endif	// (!defined(JEAN_WIN32))

#ifdef JEAN_WIN32

#ifndef _MSC_VER
#error on Windows platform, ONLY support VC to compile
#endif	// _MSC_VER

#if _MSC_VER < 1500
#error on Windows platform, ONLY support vc2008 or above
#endif //_MSC_VER < 1500

/* 要求多线程版本C++运行库 */
#ifndef _MT
#error on Windows platform, C Run-Time Libraries of multiple thread version is needed
#endif

/*
 *	在win32环境下，主要使用winsock2，所以要求必须是win NT 4.0或
 *	以上系统
 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif	// _WIN32_WINNT

#if _WIN32_WINNT < 0x0400
#error "TryEnterCricalSection requires _WIN32_WINNT >= 0x0400"
#endif

#pragma warning( disable : 4800 )
#pragma warning( disable : 4786 )
#pragma warning( disable : 4355 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4250 )
#pragma warning( disable : 4273 )
#pragma warning( disable : 4275 )
#pragma warning( disable : 4503 )  
#pragma warning( disable : 4005 )
#pragma warning( disable : 6258 )
#pragma warning( disable : 6326 )

#if _MSC_VER >= 1400
#define _CRT_SECURE_NO_DEPRECATE 1  // C4996 '<C function>' was declared deprecated/
#endif
#if _MSC_VER >= 1300
#pragma warning( 4 : 4996 ) // C4996 'std::<function>' was declared deprecated
#endif

#endif	// JEAN_WIN32

#endif	// __JEAN_PLATFORM_H__