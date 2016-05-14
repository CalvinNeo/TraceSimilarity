#pragma once

#pragma comment(lib, "WS2_32")

using namespace std;

#define RESULTPORT 15777
#define REQUESTPORT 15778
#define IP "127.0.0.1"
#define MAX_BUFFER 2048

void return_by_socket();