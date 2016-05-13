#include "CoordSimilarity.h"
#include <windows.h>

double dis(int i, int j);
inline double min3(double f1, double f2, double f3);

std::vector<Point> trace1, trace2;

const double UNTRAVELED = -10.0;
const int maxn = 101;

CoordSimilarity CoordCompare(std::vector<Point> t1, std::vector<Point> t2, bool timeissue) {

	trace1 = t1;
	trace2 = t2;
	int p = t1.size();
	int q = t2.size();

	std::vector<std::vector<double>> ca;

	for (int i = 0;i < p;i++)
	{
		std::vector<double> tmp;
		for (int j = 0;j < q;j++)
		{
			if (i == 0 && j == 0)
			{
				tmp.push_back(dis(0, 0));
			}
			else if (i > 0 && j == 0)
			{
				tmp.push_back(max(ca[i - 1][0], dis(i, 0)));
			}
			else if (i == 0 && j > 0)
			{
				tmp.push_back(max(tmp[j - 1], dis(0, j)));
			}
			else if (i > 0 && j > 0)
			{
				tmp.push_back(max(min3(ca[i - 1][j], ca[i - 1][j - 1], tmp[j - 1]), dis(i, j)));
			}
		}
		ca.push_back(tmp);
	}

	CoordSimilarity coord_res;
	coord_res.two_similarity = ca[p - 1][q - 1];

	int b1[maxn], b2[maxn];
	for (int i = 0;i < p;i++) b1[i] = 0;
	for (int i = 0;i < q;i++) b2[i] = 0;

	double lim_dis = ca[p - 1][q - 1];

	for (int t = 1;t <= 100;t++)
	{
		int x = -1, y = -1;
		for (int i = 0;i < p;i++)
		{
			for (int j = 0;j < q;j++)
			{
				if (b1[i] && b2[j] && (ca[i][j] < ca[x][y] || x == -1))
				{
					x = i;
					y = j;
				}
			}
		}
		if (x == -1) break;
		if (ca[x][y] > lim_dis) break;
		b1[x] = b2[y] = t;
		int l1, r1, l2, r2;
		for (l1 = x - 1;l1 > 0;l1--)
			if (ca[l1][y] <= lim_dis) b1[l1] = t;
			else break;
		for (r1 = x + 1;r1 < p;r1++)
			if (ca[r1][y] <= lim_dis) b1[r1] = t;
		for (l2 = y - 1;l2 > 0;l2--)
			if (ca[x][l2] <= lim_dis) b2[l2] = t;
		for (r2 = y + 1;r2 < q;r2++)
			if (ca[x][r2] <= lim_dis) b2[r2] = t;
		TwoTraceSection tt(l1, r1, l2, r2);
		coord_res.trace_section.push_back(tt);
	}

	return coord_res;

}

double dis(int i, int j) {

	return sqrt(pow(trace1[i].x * 1000 - trace2[j].x * 1000, 2) + pow(trace1[i].y * 1000 - trace2[j].y * 1000, 2));
}

inline double min3(double f1, double f2, double f3) {

	return min(f1, min(f2, f3));
}

CoordSimilarity CoordList(std::vector<Point> t1, std::vector< std::vector<Point> > tlist, bool timeissue) {
	return CoordSimilarity();
}