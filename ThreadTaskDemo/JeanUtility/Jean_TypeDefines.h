//基本数据类型定义

#pragma once
#ifndef __JEAN_TYPEDEFINE_H__
#define __JEAN_TYPEDEFINE_H__

/* JeanUtility专用返回值类型 */
typedef long JeanNetResult;


/*32 位和 64 位数据模型
				ILP32	LP64	LLP64	ILP64
char			8		8		8			8
short			16		16		16			16
int				32		32		32			64
long			32		64		32			64
long long	64		64		64			64
指针			32		64		64			64

	Linux64使用LP64模型，Windows64使用LLP64模型
	Linux32和Windows32都使用IPL32
*/

//写文件格式或网络协议相关的结构体时，必须用以下定义的定长类型
typedef char						int8;
typedef unsigned char			uint8;

typedef short						int16;
typedef unsigned short			uint16;

typedef	long						kfint32;
typedef	unsigned long			kfuint32;

typedef	long long				int64;
typedef	unsigned long long	uint64;

#if defined(_MSC_VER)
#define JEAN_INT64(n) n##LL
#endif

#endif	// __JEAN_TYPEDEFINE_H__






