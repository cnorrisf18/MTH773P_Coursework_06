#include "EurOption.h"
#include <vector>
#include <cmath>
using namespace std;


double EurOption::PriceByBinomial(double S0, double sigma, double r, int N) const
{
	//const int N = 100; //number of time steps
	const double delta = m_T / N;
	const double u = exp(sigma * sqrt(delta));
	const double d = 1.0 / u;
	const double R = exp(r * delta) - 1.0;

	const double qu = (1.0 + R - d) / (u - d);
	const double qd = 1.0 - qu;

	vector<double> v(N + 1);
	for (int i = 0; i <= N; ++i)
	{
		const double ST = S0 * pow(u, i) * pow(d, N - i);
		v[i] = payoff(ST);
	}
	for (int n = N - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			v[i] = (qu * v[i + 1] + qd * v[i]) / (1.0 + R);
		}
	}
	return v[0];
}

double EurOption::PriceByTrinomial(double S0, double sigma, double r, int N) const
{
	const double lambda = 2.0;
	const double h = m_T / N;
	const double M = exp(r * h);
	const double V = exp(2.0 * r * h) * (exp(pow(sigma, 2) * h) - 1);
	const double R = exp(r * h) - 1.0;

	const double u = exp(lambda * sigma * sqrt(h));
	const double d = 1.0 / u;


	const double qu = ((V + pow(M, 2) - M) * u - (M - 1)) / ((u - 1) * (pow(u, 2) - 1));
	const double qd = (pow(u, 2) * (V + pow(M, 2) - M) - pow(u, 3) * (M - 1)) / ((u - 1) * (pow(u, 2) - 1));
	const double qnc = 1 - qu - qd;

	vector<double> v(N + 1);
	for (int i = 0; i <= N; ++i)
	{
		const double ST = S0 * pow(u, i) * pow(d, N - i);
		v[i] = payoff(ST);
	}
	for (int n = N - 1; n >= 0; --n)
	{
		for (int i = 0; i <= n; ++i)
		{
			v[i] = (qu * v[i + 1] + qd * v[i] + qnc * v[i]) / (1.0 + R);
		}
	}
	return v[0];
}