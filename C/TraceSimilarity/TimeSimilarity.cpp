#include <boost/numeric/ublas/matrix.hpp>

#include <string>
#include <time.h>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include "def.h"
#include "TimeSimilarity.h"

std::vector<Point> AsPointList(std::vector<TPoint> & t) {
	// This function convert vector<TPoint> to vector<Point> 
	// This is deprecated for "typedef Point TPoint" is on TODO list
	std::vector<Point> c;
	c.resize(t.size());
	for (int i = 0; i < t.size(); i++)
	{
		c[i] = Point(t[i].x, t[i].y);
	}
	return c;
}

inline double distance(const Point & p1, const Point & p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

TimeSimilarity TimeCompare(std::vector<TPoint> & t1, std::vector<TPoint> & t2) {
	std::vector<Point> pl1 = AsPointList(t1), pl2 = AsPointList(t2);
	CoordSimilarity coorsim = CoordCompare(pl1, pl2, true);
	// TODO total_xy_diff， diffs_xy 以后直接从郑涌获得
	std::vector<double> diffs_t; // 每一段的时间相似度
	//std::vector<double> diffs_xy; // 每一段的距离相似度
	double total_time_dif = { 0.0 };
	double total_xy_diff = { 0.0 };
	double elapse1 = t1[t1.size() - 1].t - t1[0].t;
	double elapse2 = t2[t2.size() - 1].t - t2[0].t;
	double maxelapse = elapse1 > elapse2 ? elapse1 : elapse2;
	for (int i = 0; i < coorsim.trace_sections.size(); i++)
	{
		// assume [b1, e1) NOT [b1, e1]
		int b1 = coorsim.trace_sections[i].t1_begin, e1 = coorsim.trace_sections[i].t1_end;
		int b2 = coorsim.trace_sections[i].t2_begin, e2 = coorsim.trace_sections[i].t2_end;
		int len1 = e1 - b1, len2 = e2 - b2;
		int maxlen = len1 > len2 ? len1 : len2;
		int pi2 = b2;
		diffs_t.push_back(0.0);
		//diffs_xy.push_back(0.0);
		for (int pi1 = b1; pi1 < e1; pi1++)
		{
			const Point & p1 = t1[pi1];
			//bool next_time_closer = (pi2 + 1 >= e2 || abs((long long)(t1[pi1].t - t2[pi2].t)) < abs((long long)(t1[pi1].t - t2[pi2 + 1].t)) ) ? false : true;
			// 是否下面一个点更接近
			//bool next_xy_closer = (pi2 + 1 >= e2 || distance(t1[pi1], t2[pi2]) < distance(t1[pi1], t2[pi2 + 1])) ? false : true;
			while (!(pi2 + 1 >= e2 || distance(t1[pi1], t2[pi2]) < distance(t1[pi1], t2[pi2 + 1]))) {
				pi2++;
			}
			//diffs_xy[diffs_xy.size()-1] += distance(t1[pi1], t2[pi2]);
			diffs_t[diffs_t.size()-1] += abs(((long double)t1[pi1].t - (long double)t2[pi2].t) / maxelapse);
		}
		total_xy_diff += coorsim.trace_sections[i].coord_sim;
		total_time_dif += diffs_t[diffs_t.size() - 1];
	}
	TimeSimilarity timesim;
	// typedef CoordSimilarity TimeSimilarity
	timesim.trace_sections = coorsim.trace_sections;
	// 可能为负，这边要注意一下
	timesim.two_similarity = (total_xy_diff * total_time_dif);
	return timesim;
}

TimeSimilarityList TimeSort(std::vector<TPoint> & t1, std::vector< std::vector<TPoint> > & tlist) {
	using namespace std;
	vector<pair<int, double>> s;
	for (int i = 0; i < tlist.size(); i++)
	{
		TimeSimilarity ts = TimeCompare(t1, tlist[i]);
		s.push_back(make_pair(i, ts.two_similarity));
	}
	sort(s.begin(), s.end(), [](const pair<int, double> & x, const pair<int, double> & y) -> bool {return x.first < y.first; });
	//sort(s.begin, s.end(), [&](auto x, auto y) {return x.first < y.first; });
	return TimeSimilarityList();
}