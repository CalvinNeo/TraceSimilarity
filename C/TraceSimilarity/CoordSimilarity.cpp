#include "CoordSimilarity.h"
#include <windows.h>
#include <type_traits>
#include <algorithm>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::matrix<double> doubletable;
typedef boost::numeric::ublas::matrix<int> inttable;

double totalLen(std::vector<Point> & t, int l = 0, int r = 0);
inline double simpleDistance(Point a, Point b);
double frechetSimilar(std::vector<Point> & t1, int l1, int r1, std::vector<Point> & t2, int l2, int r2);
doubletable frechetDistance(std::vector<Point> & t1, std::vector<Point> & t2, doubletable & dis);
inline double min3(double f1, double f2, double f3);
bool cmpKthSim(kth_similarity a, kth_similarity b);
bool cmpTwoSim(TwoTraceSection a, TwoTraceSection b);
bool cmpSim(TraceSection a, TraceSection b);

//const int maxn = 101;

CoordSimilarity CoordCompare(std::vector<Point> & t1, std::vector<Point> & t2, bool timeissue) {
	//static_assert(std::is_base_of<Point, T>::value);

	int p = t1.size();
	int q = t2.size();
	double len1 = totalLen(t1);
	double len2 = totalLen(t2);
	double length = 0;

	doubletable dis(p, q);
	doubletable frechet(p, q);
	frechet = frechetDistance(t1, t2, dis);

	for (int i = 0;i < min(p, q);i++) {
		for (int j = 0;j < min(p, q);j++) {
			length += dis(i, j);
		}
	}
	if (p != q) length += dis(p - 1, q - 1);

	CoordSimilarity coord_res;
	length = min(max(len1, len2), length);
	coord_res.two_similarity = 1 - frechet(p - 1, q - 1) / length;
	coord_res.trace_sections.clear();

	const double eps = 1e-6;
	double rate = 1.0;
	double lim_dis = length * 2 / (p + q);

	inttable level(p, q);

	for (int i = 0;i < p;i++) {
		for (int j = 0;j < q;j++) {
			if (dis(i, j) <= rate * lim_dis + eps) {
				if (i > 0 && j > 0) level(i, j) = level(i - 1, j - 1) + 1;
				else level(i, j) = 1;
			}
			else level(i, j) = 0;
		}
	}

	//int b1[maxn], b2[maxn];
	//for (int i = 0;i < p;i++) b1[i] = 0;
	//for (int i = 0;i < q;i++) b2[i] = 0;

	for (int t = 1;t <= 100;t++) {
		int x = -1, y = -1;
		for (int i = 0;i < p;i++) {
			for (int j = 0;j < q;j++) {
				if (x == -1 || level(i, j)>level(x, y)) {
					x = i;
					y = j;
				}
			}
		}
		if (level(x, y) < 3) break;
		int l1, l2, k;
		for (k = 0;x > k && y > k && level(x - k, y - k) > 0;k++) {
			level(x - k, y - k) = 0;
		}
		double c_sim = frechetSimilar(t1, x - k, x + 1, t2, y - k, y + 1);
		if (c_sim > 0.5 - eps) {
			TwoTraceSection tt(x - k, x + 1, y - k, y + 1, c_sim);
			coord_res.trace_sections.push_back(tt);
		}
	}
	sort(coord_res.trace_sections.begin(), coord_res.trace_sections.end(), cmpTwoSim);
	return coord_res;
}

CoordSimilarityList CoordSort(std::vector<Point> & t1, std::vector< std::vector<Point> > & tlist, bool timeissue) {
	CoordSimilarityList coord_list;
	const double level1 = 0.7;
	for (int i = 0;i < tlist.size();i++) {
		CoordSimilarity coord_sim = CoordCompare(t1, tlist[i]);
		if (coord_sim.two_similarity > level1) {
			coord_list.similarities.push_back(std::make_pair(i, coord_sim.two_similarity));
			for (int j = 0;j < coord_sim.trace_sections.size();j++) {
				coord_list.trace_sections.push_back(TraceSection(i, coord_sim.trace_sections[j]));
			}
		}
	}
	sort(coord_list.similarities.begin(), coord_list.similarities.end(), cmpKthSim);
	sort(coord_list.trace_sections.begin(), coord_list.trace_sections.end(), cmpSim);
	return coord_list;
}

bool cmpKthSim(kth_similarity a, kth_similarity b) {
	return a.second > b.second;
}

bool cmpTwoSim(TwoTraceSection a, TwoTraceSection b) {
	return a.coord_sim > b.coord_sim;
}

bool cmpSim(TraceSection a, TraceSection b) {
	return a.coord_sim > b.coord_sim;
}

double frechetSimilar(std::vector<Point> & t1, int l1, int r1, std::vector<Point> & t2, int l2, int r2) {
	int p = r1 - l1;
	int q = r2 - l2;

	//init distance
	doubletable dis(p, q);
	for (int i = 0;i < p;i++) {
		for (int j = 0;j < q;j++) {
			dis(i, j) = simpleDistance(t1[i + l1], t2[j + l2]);
		}
	}

	doubletable frechet(p, q);
	for (int i = 0;i < p;i++) {
		for (int j = 0;j < q;j++) {
			if (i == 0 && j == 0) {
				frechet(i, j) = dis(0, 0);
			}
			else if (i > 0 && j == 0) {
				frechet(i, j) = (max(frechet(i - 1, 0), dis(i, 0)));
			}
			else if (i == 0 && j > 0) {
				frechet(i, j) = (max(frechet(i, j - 1), dis(0, j)));
			}
			else if (i > 0 && j > 0) {
				frechet(i, j) = (max(min3(frechet(i - 1, j), frechet(i - 1, j - 1), frechet(i, j - 1)), dis(i, j)));
			}
		}
	}
	double len1 = totalLen(t1, l1, r1);
	double len2 = totalLen(t2, l2, r2);
	double length = 0;
	for (int i = 0;i < min(p, q);i++) {
		for (int j = 0;j < min(p, q);j++) {
			length += dis(i, j);
		}
	}
	if (p != q) length += dis(p - 1, q - 1);
	length = min(max(len1, len2), length);
	return  1 - frechet(p - 1, q - 1) / length;
}

doubletable frechetDistance(std::vector<Point> & t1, std::vector<Point> & t2, doubletable & dis) {
	int p = t1.size();
	int q = t2.size();

	//init distance
	dis.clear();
	for (int i = 0;i < p;i++) {
		for (int j = 0;j < q;j++) {
			dis(i, j) = simpleDistance(t1[i], t2[j]);
		}
	}

	doubletable frechet(p, q);
	for (int i = 0;i < p;i++) {
		for (int j = 0;j < q;j++) {
			if (i == 0 && j == 0) {
				frechet(i, j) = dis(0, 0);
			}
			else if (i > 0 && j == 0) {
				frechet(i, j) = (max(frechet(i - 1, 0), dis(i, 0)));
			}
			else if (i == 0 && j > 0) {
				frechet(i, j) = (max(frechet(i, j - 1), dis(0, j)));
			}
			else if (i > 0 && j > 0) {
				frechet(i, j) = (max(min3(frechet(i - 1, j), frechet(i - 1, j - 1), frechet(i, j - 1)), dis(i, j)));
			}
		}
	}
	return frechet;
}

//求扩大1000倍后的欧几里得距离
inline double simpleDistance(Point a, Point b) {
	return sqrt(pow(a.x * 1000 - b.x * 1000, 2) + pow(a.y * 1000 - b.y * 1000, 2));
}

//求某段轨迹的折线长度
double totalLen(std::vector<Point> & t, int l, int r) {
	if (r == 0) r = t.size();
	double res = 0;
	for (int i = l + 1;i < r;i++) {
		res += simpleDistance(t[i - 1], t[i]);
	}
	return res;
}

inline double min3(double f1, double f2, double f3) {
	return min(f1, min(f2, f3));
}
