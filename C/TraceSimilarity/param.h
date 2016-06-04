#pragma once
#include "interface.h"
// 如果使用typedef在interface.h中定义，则或者include interface.h，或者加入下方前置声明（去掉函数声明中的struct）
//typedef struct Sync_Sock Boost_Sock;
void paramop_time(Boost_Sock * sender, const char * data, size_t len);
void paramop_coord(Boost_Sock * sender, const char * data, size_t len);