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


/**
 * \brief Beale function
 *
 * A two-dimensional function, The global minimum is 0
 * at (3, 0.5).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double beale(const double* x, const int n)
{
	return pow(1.5 - x[0] + x[0] * x[1], 2) +
		pow(2.25 - x[0] + x[0] * x[1] * x[1], 2) +
		pow(2.625 - x[0] + x[0] * pow(x[1], 3), 2);
}


/**
 * \brief Bohachevsky function
 *
 * A two-dimensional function, The global minimum is 0
 * at (0, 0).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double bohachevsky(const double* x, const int n)
{
	return x[0] * x[0] + 2.0 * x[1] * x[1] - 0.3 * cos(3.0 * M_PI * x[0]) -
		0.4 * cos(4.0 * M_PI * x[1]) + 0.7;
}
