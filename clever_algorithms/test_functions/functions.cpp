#include "functions.h"
#define _USE_MATH_DEFINES
#include <math.h>


/**
 * \brief Ackley function
 *
 * It has a global minimum 0 at x_i = 0.
 * \param x input var
 * \param n the dimension of input
 * \return computed result
 */
double ackley(const double* x, const int n)
{
	double s2;
	double s1 = s2 = 0.0;
	for (int i = 0; i < n; i++)
	{
		const double t = x[i];
		s1 += t * t;
		s2 += cos(2.0 * M_PI * x[i]);
	}
	return -20.0 * exp(-0.2 * sqrt(s1 / n)) - exp(s2 / n) + 20.0 + M_E;
}
