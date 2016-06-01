#include "param.h"
#include "interface.h"
#include "def.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"


void paramop_time() {

}

void paramop_coord(char * str, size_t len) {
	using namespace boost::asio;
	const paramop_msg* ppm = reinterpret_cast<const paramop_msg*>(str); //do not delete ppm

}

