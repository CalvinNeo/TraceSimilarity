#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#define CHECKED_ALL
#ifdef CHECKED_ALL
//#pragma comment(lib, "libboost_random-vc140-mt-sgd-1_60.lib") 
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#endif

#include <tuple>
#include <algorithm>
#include <vector>
#include <map>
#include "time.h"
#include <random>
#include "math.h"
#include <functional>   // std::minus
#include <numeric>      // std::accumulate

#include "xNES.h"

using namespace boost::numeric;
using std::cout;
using std::endl;

double costfunc(double x) {
	//return -(x - 3)*(x - 6)*(x - 7)*(x - 10);
	return - pow((x - 80), 2) + 10;
}

void qsort2(std::vector<double> & master, std::vector<double> & slave1, std::vector<double> & slave2, int start, int end) {
	if (start >= end) return;
	double mid = master[end];
	int left = start, right = end - 1;
	while (left < right) {
		while (master[left] > mid && left < right) left++;
		while (master[right] <= mid && left < right) right--;
		std::swap(master[left], master[right]);
		std::swap(slave1[left], slave1[right]);
		std::swap(slave2[left], slave2[right]);
	}
	if (master[left] <= master[end])//防止本来就是有序的
	{
		std::swap(master[left], master[end]);
		std::swap(slave1[left], slave1[end]);
		std::swap(slave2[left], slave2[end]);
	}
	else
		left++;
	qsort2(master, slave1, slave2 ,start, left - 1);
	qsort2(master, slave1, slave2 ,left + 1, end);
}

int test() {
	std::vector<double> master(5);
	std::vector<double> slave1(5);
	std::vector<double> slave2(5);
	for (int i = 0; i < 5; i++)
	{
		master[i] = 5 - i;
		slave1[i] = i;
		slave2[i] = i;
	}
	for (int i = 0; i < 5; i++)
	{
		cout << master[i] << " " << slave1[i] << slave2[i] << endl;
	}
	cout << "---------------------------------" << endl;
	qsort2(master, slave1, slave2, 0, 4);
	for (int i = 0; i < 5; i++)
	{
		cout << master[i] << " " << slave1[i] << slave2[i] << endl;
	}
	return 0;
}

int xNES() {
#ifdef CHECKED_ALL
	boost::random::mt19937 seed;
#else
	std::ranlux64_base_01 seed;
	seed.seed(time(NULL));
#endif
	int d = 1;
	int miu = 0.0;
	int A = 1.0;
	double sigma = pow(A, 1.0 / d);
	double B = A / sigma;
	int itertimes = 0, maxitertimes = 200;
	int n = 4 + (double)ceil(3 * log10(d));
	double ita_sigma = 0.6 * (3 + log10(d)) / d / sqrt(d), ita_B = ita_sigma;
	double ita_miu = 1.0;

	std::vector<double> z(n), x(n), u(n), fx(n);
	std::vector<std::pair<double, double>> p(n);

	while (itertimes < maxitertimes) {
		itertimes++;
		double denominator = 0.0;
		for (int i = 0; i < n; i++)
		{
			denominator += std::max(0.0, log(n / 2.0 + 1) - log(i + 1.0));
		}
		for (int i = 0; i < n; i++)
		{
			u[i] = std::max(0.0, log(n / 2.0 + 1) - log(i + 1.0)) / denominator - 1.0 / n;
		}
		for (int i = 0; i < n; i++)
		{
#ifdef CHECKED_ALL
			boost::uniform_01<boost::mt19937&> u01(seed);
			boost::normal_distribution<> nd(0, 1.0);
#else
			std::normal_distribution<double> nd(0, 1.0);
#endif
			z[i] = nd(seed);
			x[i] = miu + sigma * B * z[i];
			fx[i] = costfunc(x[i]);
		}
		// sort
		qsort2(fx, z, x, 0, fx.size()-1);
		std::transform(u.begin(), u.end(), z.begin(), p.begin(), [=](double a, double b) {return std::pair<double, double>(a, b); });
		double G_delta = std::accumulate(p.begin(), p.end(), 0, [=](double a, std::pair<double, double> uizi) {return a + uizi.first * uizi.second; });
		double G_M = std::accumulate(p.begin(), p.end(), 0, [=](double a, std::pair<double, double> uizi) {return a + uizi.first * (uizi.second * uizi.second - 1); });
		double G_sigma = G_M / d;
		double G_B = G_M - G_sigma * 1;
		miu += ita_miu * sigma * B * G_delta;
		sigma = sigma * exp(ita_sigma / 2.0 * G_sigma);
		B = B * exp(ita_B / 2.0 * G_B);
	}
	for (int i = 0; i < n; i++)
	{
		printf("%f ", z[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%f ", x[i]);
	}
	printf("\n");
	return 0;
}