#pragma once
#ifndef __INTERFACE_H__
//#define __INTERFACE_H__

#pragma message("H")
#pragma comment(lib, "WS2_32")

#define RESULTPORT 15777
#define REQUESTPORT 15777
#define IP "127.0.0.1"
#define MAX_BUFFER 2048

void boost_return();
void file_return();
void return_by_socket();

char * result_encode(struct TimeSimilarity);
char * result_encode(struct TimeSimilarityList);
char * result_encode(struct CoordSimilarity);
char * result_encode(struct CoordSimilarityList);


#endif