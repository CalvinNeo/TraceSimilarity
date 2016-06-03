#pragma once

typedef struct Sync_Sock Boost_Sock;
void paramop_time(Boost_Sock * sender, const char * data, size_t len);
void paramop_coord(Boost_Sock * sender, const char * data, size_t len);