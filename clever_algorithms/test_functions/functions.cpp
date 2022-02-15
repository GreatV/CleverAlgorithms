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


/**
 * \brief Booth function
 *
 * A two-dimensional function, The global minimum is 0
 * at (1, 3).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double booth(const double* x, const int n)
{
	return pow(x[0] + 2 * x[1] - 7, 2) +
		pow(2 * x[0] + x[1] - 5, 2);
}


/**
 * \brief Box-Betts function
 *
 * A three-dimensional function. The global minimum is 0
 * at (1, 10, 1).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double box_betts(const double* x, const int n)
{
	const double x0 = x[0];
	const double x1 = x[1];
	const double x2 = x[2];
	double sum = 0.0;
	for (int i = 1; i <= 10; i++)
		sum += pow(exp(-0.1 * i * x0) - exp(-0.1 * i * x1) -
		           (exp(-0.1 * i) - exp(-1.0 * i)) * x2, 2.0);
	return sum;
}

/**
 * \brief Branin function
 *
 * It has a global minimum function value of 0.398
 * at the points (−3.142, 12.275), (3.142, 2.275) and (9.425, 2.425).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double branin(const double* x, const int n)
{
	const double x0 = x[0];
	const double s = x[1] - (5.1 / (4.0 * M_PI * M_PI) * x0 - 5.0 / M_PI) * x0 - 6.0;
	return s * s + 10 * (1.0 - 1.0 / (8.0 * M_PI)) * cos(x0) + 10.0;
}
