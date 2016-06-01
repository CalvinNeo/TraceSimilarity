#include "param.h"
#include "interface.h"
#include "def.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include <boost/algorithm/string.hpp>

void paramop_time() {

}

void paramop_coord(char * data, size_t len) {
	using namespace boost;
	using namespace std;
	const paramop_msg* ppm = reinterpret_cast<const paramop_msg*>(data); //do not delete ppm
	vector<string> SplitVec;
	string str1(ppm->op);
	split(SplitVec, str1, is_any_of(","), token_compress_on); // SplitVec == { "hello abc","ABC","aBc goodbye" }
	if (SplitVec.size() >= 2) {
		printf("Optimizing Parameter %s From %s To %s\n", SplitVec[0].c_str(), SplitVec[1].c_str(), SplitVec[2].c_str());
	}
	else {
		printf("Invalid Call\n");
	}
}

