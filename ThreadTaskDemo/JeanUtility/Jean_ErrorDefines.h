#pragma once
#ifndef __JEAN_ERRORDEFINES_H__
#define __JEAN_ERRORDEFINES_H__

//ԭ��>=0��ʾ�ɹ� <0��ʾʧ��
#define JEAN_OK 0
//�жϵ�ǰֵ�Ƿ�Ϊ��ʧ�ܡ�
#define JEAN_FAILED( jeanResult ) ( jeanResult != JEAN_OK )

//�жϵ�ǰֵ�Ƿ�Ϊ���ɹ���
#define JEAN_SUCCEEDED( jeanResult ) ( jeanResult == JEAN_OK )

#endif	// __JEAN_ERRORDEFINES_H__

