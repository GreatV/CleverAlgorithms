#define _USE_MATH_DEFINES

#include "test_functions.h"
#include <cmath>


double ackley_function(std::vector<double> & x)
{
	const double a = 20;
	const double b = 0.2;
	const double c = 2.0 * M_PI;

	double sum0 = 0.0;
	for (const double xi : x)
	{
		sum0 += xi * xi;
	}
	sum0 /= x.size();
	const double term0 = -a * exp(-b * sqrt(sum0));

	double sum1 = 0.0;
	for (const double xi : x)
	{
		sum1 += cos(c * xi);
	}
	sum1 /= x.size();
	const double term1 = -exp(sum1);

	const double y = term0 + term1 + a + exp(1);

	return y;
}
