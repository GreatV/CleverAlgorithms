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


/**
 * \brief Camel function
 * A two-dimensional function, The global minimum is 0
 * at (0, 0).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double camel3(const double* x, const int n)
{
	const double x02 = x[0] * x[0];
	const double x04 = x02 * x02;
	const double x06 = x04 * x02;
	return 2 * x02 - 1.05 * x04 + x06 / 6.0 + x[0] * x[1] * x[1] * x[1];
}


/**
 * \brief Chichinadze function
 * A two-dimensional function, The global minimum is 43.3159
 * at  (5.90133, 0.5).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double chichinadze(const double* x, const int n)
{
	return x[0] * x[0] - 12 * x[0] + 11 + 10 * cos(M_PI / 2.0 * x[0])
		+ 8 * sin(5 * M_PI * x[0])
		- exp(-(x[1] - 0.5) * 0.5) / sqrt(5.0);
}


static double dis[] = {
	1.27,
	1.69, 1.43,
	2.04, 2.35, 2.43,
	3.09, 3.18, 3.26, 2.85,
	3.20, 3.22, 3.27, 2.88, 1.55,
	2.86, 2.56, 2.58, 2.59, 3.12, 3.06,
	3.17, 3.18, 3.18, 3.12, 1.31, 1.64, 3.00,
	3.21, 3.18, 3.18, 3.17, 1.70, 1.36, 2.95, 1.32,
	2.38, 2.31, 2.42, 1.94, 2.85, 2.81, 2.56, 2.91, 2.97
};

/**
 * \brief Cola function
 * A 17-dimensional function, The global minimum is 11.7464.
 * \param x input var
 * \param n dimension, n = 17
 * \return computed result
 */
double cola(const double* x, const int n)
{
	double sum = 0.0;
	int i;
	int k = 1;
	double mt[20] = {0, 0, 0, 0};
	for (i = 4; i < 20; i++)
		mt[i] = x[i - 3];
	for (i = 1; i < 10; i++)
		for (int j = 0; j < i; j++)
		{
			double temp = 0.0;
			for (int t = 0; t < 2; t++)
				temp += (mt[i * 2 + t] - mt[j * 2 + t]) * (mt[i * 2 + t] - mt[j * 2 + t]);
			sum += (dis[k - 1] - sqrt(temp)) * (dis[k - 1] - sqrt(temp));
			k++;
		}
	return sum;
}

/**
 * \brief Colville function
 * A 4-dimensional function, The global minimum is 0,
 * at the point(1, 1, 1, 1).
 * \param x input var
 * \param n dimension, n = 4
 * \return computed result
 */
double colville(const double* x, const int n)
{
	return 100 * pow(x[0] - x[1] * x[1], 2)
		+ pow(1 - x[0], 2)
		+ 90 * pow(x[3] - x[2] * x[2], 2)
		+ pow(1 - x[2], 2)
		+ 10.1 * (pow(x[1] - 1, 2) + pow(x[3] - 1, 2))
		+ 19.8 * (x[1] - 1) * (x[3] - 1);
}


static double sign(const double x)
{
	return x < 0.0 ? -1.0 : 1.0;
}


/**
 * \brief Corana function
 * A 4-dimensional function, The global minimum is 0.
 * \param x input var
 * \param n dimension, n = 4
 * \return computed result
 */
double corana(const double* x, const int n)
{
	const double d[] = {1, 1000, 10, 100};
	double s = 0.0;
	for (int i = 0; i < 4; i++)
	{
		double z = floor(fabs(x[i] / 0.2) + 0.49999) * sign(x[i]) * 0.2;
		if (fabs(x[i] - z) < 0.05)
		{
			s += 0.15 * (z - 0.05 * sign(z)) * (z - 0.05 * sign(z)) * d[i];
		}
		else
		{
			s += d[i] * x[i] * x[i];
		}
	}
	return s;
}


/**
 * \brief Easom function
 * A 2-dimensional function, The global minimum is -1,
 * at point (-pi, pi).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double easom(const double* x, const int n)
{
	return -cos(x[0]) * cos(x[1]) * 
		exp(- (x[0] - M_PI) * (x[0] - M_PI) - (x[1] - M_PI) * (x[0] - M_PI));
}


/**
 * \brief Egg holder function
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double eggholder(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n - 1; i++)
	{
		sum += -(x[i + 1] + 47.0) * sin(sqrt(fabs(x[i + 1] + x[i] * 0.5 + 47.0))) +
			sin(sqrt(fabs(x[i] - (x[i + 1] + 47.0)))) * (-x[i]);
	}
	return sum;
}


/**
 * \brief Gear function
 *
 * A 4-dimensional function, The global minimum is 2.7e-12,
 * at (16, 19, 43, 49).
 * \param x input var
 * \param n dimension, n = 4
 * \return computed result
 */
double gear(const double* x, const int n)
{
	const double t = 1.0 / 6.931 - floor(x[0]) * floor(x[1]) / (floor(x[2]) * floor(x[3]));
	return t * t;
}


/**
 * \brief GoldsteinPrice function
 *
 * A 2-dimensional function, The global minimum is 3,
 * at (0, -1).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double goldstein_price(const double* x, const int n)
{
	return (1.0 + pow(x[0] + x[1] + 1.0, 2) *
			(19.0 - 14.0 * x[0] + 3.0 * x[0] * x[0] - 14.0 * x[1]
				+ 6.0 * x[0] * x[1] + 3.0 * x[1] * x[1])) *
		(30.0 + pow(2.0 * x[0] - 3.0 * x[1], 2) *
			(18.0 - 32.0 * x[0] + 12.0 * x[0] * x[0] + 48.0 * x[1]
				- 36.0 * x[0] * x[1] + 27.0 * x[1] * x[1]));
}


/**
 * \brief Griewank function
 *
 * A 2-dimensional function, The global minimum is 0,
 * at (0, 0).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double griewank(const double* x, const int n)
{
	double sum = 0;
	double prod = 1;
	for (int i = 0; i < 10; i++)
	{
		sum += x[i] * x[i];
		prod *= cos(x[i] / sqrt(static_cast<double>(i + 1)));
	}
	return sum / 4000.0 - prod + 1;
}
