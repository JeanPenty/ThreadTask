//�����������Ͷ���

#pragma once
#ifndef __JEAN_TYPEDEFINE_H__
#define __JEAN_TYPEDEFINE_H__

/* JeanUtilityר�÷���ֵ���� */
typedef long JeanNetResult;


/*32 λ�� 64 λ����ģ��
				ILP32	LP64	LLP64	ILP64
char			8		8		8			8
short			16		16		16			16
int				32		32		32			64
long			32		64		32			64
long long	64		64		64			64
ָ��			32		64		64			64

	Linux64ʹ��LP64ģ�ͣ�Windows64ʹ��LLP64ģ��
	Linux32��Windows32��ʹ��IPL32
*/

//д�ļ���ʽ������Э����صĽṹ��ʱ�����������¶���Ķ�������
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






