#pragma once
#include "interface.h"
// ���ʹ��typedef��interface.h�ж��壬�����include interface.h�����߼����·�ǰ��������ȥ�����������е�struct��
//typedef struct Sync_Sock Boost_Sock;
void paramop_time(Boost_Sock * sender, const char * data, size_t len);
void paramop_coord(Boost_Sock * sender, const char * data, size_t len);