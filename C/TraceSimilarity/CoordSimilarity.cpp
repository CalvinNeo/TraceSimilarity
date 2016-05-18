#include "CoordSimilarity.h"
#include <windows.h>
#include <type_traits>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

typedef boost::numeric::ublas::matrix<double> doubletable;

double totalLen(std::vector<Point> & t);
inline double simpleDistance(Point a, Point b);
doubletable frechetDistance(std::vector<Point> & t1, std::vector<Point> & t2, doubletable & dis);
inline double min3(double f1, double f2, double f3);

const int maxn = 101;

CoordSimilarity CoordCompare(std::vector<Point> & t1, std::vector<Point> & t2, bool timeissue) {
	//static_assert(std::is_base_of<Point, T>::value);

	int p = t1.size();
	int q = t2.size();
	double len1 = totalLen(t1);
	double len2 = totalLen(t2);
	double length = 0;

	for (int i = 0;i < min(p, q);i++) {
		for (int j = 0;j < min(p, q);j++) {
			length += simpleDistance(t1[i], t2[j]);
		}
	}
	if (p != q) length += simpleDistance(t1[p - 1], t2[q - 1]);

	doubletable dis(p, q);
	doubletable frechet(p, q);
	frechet = frechetDistance(t1, t2, dis);

	CoordSimilarity coord_res;
	coord_res.two_similarity = 1 - frechet(p - 1, q - 1) / min(max(len1, len2), length);
	coord_res.trace_sections.clear();

	std::vector<std::vector<int>> level;
	const double eps = 1e-6;
	double lim_rate = frechet(p - 1, q - 1) / min(max(len1, len2), length);

	for (int i = 0;i < p;i++) {
		std::vector<int> tmp;
		for (int j = 0;j < q;j++) {
			if (dis(i, j) <= lim_rate*frechet(i, j) + eps) {
				if (i > 0 && j > 0) tmp.push_back(level[i - 1][j - 1] + 1);
				else tmp.push_back(1);
			}
			else tmp.push_back(0);
		}
		level.push_back(tmp);
	}

	for (int t = 1;t <= 100;t++) {
		int x = -1, y = -1;
		for (int i = 0;i < p;i++) {
			for (int j = 0;j < q;j++) {
				if (x == -1 || level[i][j]>level[x][y]) {
					x = i;
					y = j;
				}
			}
		}
		if (level[x][y] < 3) break;
		int l1, l2, k;
		for (k = 0;x > k && y > k && level[x - k][y - k] > 0;k++) {
			level[x - k][y - k] = 0;
		}
		TwoTraceSection tt(x - k, x + 1, y - k, y + 1);
		coord_res.trace_sections.push_back(tt);

	}


	//int b1[maxn], b2[maxn];
	//for (int i = 0;i < p;i++) b1[i] = 0;
	//for (int i = 0;i < q;i++) b2[i] = 0;

	return coord_res;

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

inline double simpleDistance(Point a, Point b) {

	return sqrt(pow(a.x * 1000 - b.x * 1000, 2) + pow(a.y * 1000 - b.y * 1000, 2));
}

double totalLen(std::vector<Point> & t) {

	double res = 0;
	for (int i = 1;i < t.size();i++) {
		res += simpleDistance(t[i - 1], t[i]);
	}
	return res;
}

inline double min3(double f1, double f2, double f3) {

	return min(f1, min(f2, f3));
}

CoordSimilarityList CoordSort(std::vector<Point> & t1, std::vector< std::vector<Point> > & tlist, bool timeissue) {
	return CoordSimilarityList();
}
