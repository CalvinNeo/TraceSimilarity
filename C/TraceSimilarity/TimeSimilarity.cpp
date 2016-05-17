#include <boost/numeric/ublas/matrix.hpp>

#include <string>
#include <time.h>
#include <vector>

#include "def.h"
#include "TimeSimilarity.h"

std::vector<Point> AsPointList(std::vector<TPoint> t) {
	std::vector<Point> c;
	c.resize(t.size());
	for (int i = 0; i < t.size(); i++)
	{
		c[i] = Point(t[i].x, t[i].y);
	}
	return c;
}

TimeSimilarity TimeCompare(std::vector<TPoint> & t1, std::vector<TPoint> & t2) {
	std::vector<Point> p1 = AsPointList(t1), p2 = AsPointList(t2);
	CoordSimilarity coorsim = CoordCompare(p1, p2, true);
	std::vector<double> p_diff;
	for (int i = 0; i < coorsim.trace_sections.size(); i++)
	{
		int b1 = coorsim.trace_sections[i].t1_begin;
		int e1 = coorsim.trace_sections[i].t1_end;
		int b2 = coorsim.trace_sections[i].t2_begin;
		int e2 = coorsim.trace_sections[i].t2_end;
		//p_diff.push_back(sqrt(t1[p1]*t1[p2]))
	}
	TimeSimilarity timesim;
	// typedef CoordSimilarity TimeSimilarity
	return TimeSimilarity();
}

TimeSimilarityList TimeSort(std::vector<TPoint> & t1, std::vector< std::vector<TPoint> > & tlist) {
	return TimeSimilarityList();
}