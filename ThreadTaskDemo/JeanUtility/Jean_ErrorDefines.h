#pragma once
#ifndef __JEAN_ERRORDEFINES_H__
#define __JEAN_ERRORDEFINES_H__

//原则：>=0表示成功 <0表示失败
#define JEAN_OK 0
//判断当前值是否为“失败”
#define JEAN_FAILED( jeanResult ) ( jeanResult != JEAN_OK )

//判断当前值是否为“成功”
#define JEAN_SUCCEEDED( jeanResult ) ( jeanResult == JEAN_OK )

#endif	// __JEAN_ERRORDEFINES_H__

