#include "param.h"
#include "interface.h"
#include "def.h"
#include "CoordSimilarity.h"
#include "TimeSimilarity.h"
#include <boost/algorithm/string.hpp>

bool paramop_time(Boost_Sock * sender, const char * data, size_t len) {
	return true;
}

bool paramop_coord(Boost_Sock * sender, const char * data, size_t len) {
	using namespace boost;
	using namespace std;
	const paramop_msg* ppm = reinterpret_cast<const paramop_msg*>(data); //do not delete ppm
	vector<string> SplitVec;
	string str1(ppm->op);
	split(SplitVec, str1, is_any_of(","), token_compress_on); // SplitVec == { "hello abc","ABC","aBc goodbye" }
	if (SplitVec.size() == 3) {
		printf("Optimizing Parameter %s From %s To %s\n", SplitVec[0].c_str(), SplitVec[1].c_str(), SplitVec[2].c_str());
		Sleep(1000);
		sender->send_str("done", 5);
		return false;
	}
	else if(SplitVec.size() == 1){
		if (SplitVec[0] == "end") {
			printf("End\n");
			//if (sender->ios_thread.joinable())
			//	sender->ios_thread.join();
			return true;
		}
		else if (SplitVec[0] == "start") {
			printf("Start\n");
			Sleep(1000);
			sender->send_str("done", 5);
			return false;
		}
	}
	else {
		printf("Invalid Call\n");
		return true;
	}
}

