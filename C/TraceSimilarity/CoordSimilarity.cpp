#include "CoordSimilarity.h"

std::vector<Point> trace1, trace2;

CoordSimilarity CoordCompare(std::vector<Point> t1, std::vector<Point> t2) {

	trace1 = t1;
	trace2 = t2;
	int p = t1.size();
	int q = t2.size();

	double fval;

	// init ca[p][q]
	double **ca = new double*[p];
	int i, j;
	for (i = 0; i < p; i++)
	{
		ca[i] = new double[q];
	}

	for (i = 0; i < p; i++)
	{
		for (j = 0; j < q; j++)
		{
			ca[i][j] = -1.0;
		}
	}

	// calc distance
	fval = Cal(ca, p - 1, q - 1);

	CoordSimilarity coord_res;
	coord_res.similarity_2 = fval;

	for (i = 0; i < p; i++)
		delete[]ca[i];
	delete[]ca;



	return coord_res;

}

double Cal(double** ca, int i, int j)
{
	if (ca[i][j] > -1.0)
	{
		return ca[i][j];
	}
	else if (i == 0 && j == 0)
	{
		ca[i][j] = dis(0, 0);
	}
	else if (i > 0 && j == 0)
	{
		ca[i][j] = max(Cal(ca, i - 1, 0), dis(i, 0));
	}
	else if (i == 0 && j > 0)
	{
		ca[i][j] = max(Cal(ca, 0, j - 1), dis(0, j));
	}
	else if (i > 0 && j > 0)
	{
		ca[i][j] = max(min3(Cal(ca, i - 1, j), Cal(ca, i - 1, j - 1), Cal(ca, i, j - 1)), dis(i, j));
	}
	else
	{
		ca[i][j] = 0xFFFFFFFF;
	}

	return ca[i][j];
}

double dis(int i, int j)
{
	return sqrt(pow(trace1[i].x - trace2[j].x, 2) + pow(trace1[i].y - trace2[j].y, 2));
}

inline double min3(double f1, double f2, double f3)
{
	return min(f1, min(f2, f3));
}

CoordSimilarity CoordList(std::vector<Point> t1, std::vector< std::vector<Point> > tlist);