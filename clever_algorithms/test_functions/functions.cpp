#include "functions.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>


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


/**
 * \brief Hansen function
 *
 * A 2-dimensional function, The global minimum is -176.54,.
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double hansen(const double* x, const int n)
{
	return (cos(1.0) + 2.0 * cos(x[0] + 2.0)
		+ 3.0 * cos(2.0 * x[0] + 3.0) + 4.0 * cos(3.0 * x[0] + 4.0)
		+ 5.0 * cos(4.0 * x[0] + 5.0)) * (cos(2.0 * x[1] + 1.0)
		+ 2.0 * cos(3.0 * x[1] + 2.0)
		+ 3.0 * cos(4.0 * x[1] + 3.0)
		+ 4.0 * cos(5.0 * x[1] + 4.0)
		+ 5.0 * cos(6.0 * x[1] + 5.0));
}


/**
 * \brief Hartman function
 *
 * The global minimum is − 3:86,
 * at (0.114, 0.556, 0.852).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double hartman3(const double* x, const int n)
{
	static double a[4][3] = {
		{3, 10, 30},
		{0.1, 10, 35},
		{3, 10, 30},
		{0.1, 10, 35}
	};
	const double c[] = {1, 1.2, 3, 3.2};
	const double p[4][3] = {
		{0.3689, 0.1170, 0.2673},
		{0.4699, 0.4387, 0.7470},
		{0.1091, 0.8732, 0.5547},
		{0.03815, 0.5743, 0.8828}
	};

	double s = 0.0;
	for (int i = 0; i < 4; i++)
	{
		double t = 0.0;
		for (int j = 0; j < n; j++)
		{
			const double t1 = x[j] - p[i][j];
			t += a[i][j] * (t1 * t1);
		}
		s
			+= c[i] * exp(-t);
	}
	return -s;
}


/**
 * \brief Hartman function
 *
 * The global minimum is -3.32,
 * at (0.201, 0.150, 0.477, 0.275, 0.311, 0.657).
 * \param x input var
 * \param n dimension, n = 6
 * \return computed result
 */
double hartman6(const double* x, const int n)
{
	static double a[4][6] = {
		{10, 3, 17, 3.5, 1.7, 8.0},
		{0.05, 10, 17, 0.1, 8, 14},
		{3, 3.5, 1.7, 10, 17, 8},
		{17, 8, 0.05, 10, 0.1, 14}
	};
	const double c[] = {1, 1.2, 3, 3.2};
	const double p[4][6] = {
		{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
		{0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
		{0.2348, 0.1415, 0.3522, 0.2883, 0.3047, 0.6650},
		{0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}
	};

	double s = 0.0;
	for (int i = 0; i < 4; i++)
	{
		double t = 0.0;
		for (int j = 0; j < n; j++)
		{
			const double t1 = x[j] - p[i][j];
			t += a[i][j] * (t1 * t1);
		}
		s += c[i] * exp(-t);
	}
	return -s;
}

/**
 * \brief Himmelblau function
 *
 * The global minimum is 0,
 * at (3, 2).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double himmelblau(const double* x, const int n)
{
	return (x[0] * x[0] + x[1] - 11.0) * (x[0] * x[0] + x[1] - 11.0) +
		(x[0] + x[1] * x[1] - 7) * (x[0] + x[1] * x[1] - 7);
}

/**
 * \brief Holzman function
 *
 * The global minimum is 0,
 * at (50, 25, 1.5).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double holzman1(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i < 100; i++)
	{
		const double ui = 25 + pow(-50.0 * log(0.01 * (i + 1)), 2.0 / 3.0);
		sum += -0.1 * (i + 1) + 
			exp(1 / x[0] * pow(ui - x[1], x[2]));
	}
	return sum;
}


/**
 * \brief Holzman function
 *
 * The global minimum is 0,
 * at (0, ..., 0).
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double holzman2(const double* x, const int n)

{
	double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		sum += i * pow(x[i], 4);
	}
	return sum;
}

/**
 * \brief Hosaki function
 *
 * The global minimum is -2.3458,
 * at (4, 2).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double hosaki(const double* x, const int n)
{
	return (1 + x[0] * (-8 + x[0] * (7 + x[0] * (-7.0 / 3.0 + x[0] * 1.0 / 4.0)))) * x[1] * x[1] * exp(-x[1]);
}


/**
 * \brief Katsuuras function
 *
 * The global minimum is 0,
 * at (0,...,0).
 * \param x input var
 * \param n dimension, n = 10
 * \return computed result
 */
double katsuuras(const double* x, const int n)
{
	double prod = 1.0;
	for (int i = 0; i < n; i++)
	{
		const int d = 32;
		double s = 0.0;
		for (int k = 1; k <= d; k++)
		{
			const double pow2 = pow(2, k);
			s += round(pow2 * x[i]) / pow2;
		}
		prod *= 1.0 + (i + 1) * s;
	}
	return prod;
}


/**
 * \brief Lennard-Jones function
 *
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double lennard_jones(const double* x, const int n)
{
	int j3;
	double E;
	const int n_atoms = n / 3;
	for (int i = 0; i < n_atoms; i++)
	{
		const int i3 = i * 3;
		for (int j = i + 1; j < n_atoms; j++)
		{
			double dz = 0.0;
			double z = x[i3] - x[j3 = j * 3];
			dz += z * z;
			z = x[i3 + 1] - x[j3 + 1];
			dz += z * z;
			z = x[i3 + 2] - x[j3 + 2];
			dz += z * z;
			if (dz < 1.0e-6)
			{
				/* one pair of atoms too near ? */
				return DBL_MAX;
			}
			else
			{
				const double dzp = 1.0 / (dz * dz * dz);
				E += (dzp - 2.0) * dzp;
			}
		}
	}
	return E;
}

/**
 * \brief Leon function
 *
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double leon(const double* x, const int n)
{
	const double a = x[1] - x[0] * x[0] * x[0];
	const double b = 1.0 - x[0];
	return 100.0 * a * a + b * b;
}

/**
 * \brief Levy function

* The global minimum is -21.502356,
 * at (1,1,1,-9.752356 ) for n = 4.
 * And global minimum is -11.504403,
 * at (1, ..., 1, ,-4.754402) for n = 5, 6, 7.
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double levy(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i <= n - 2; i++)
		sum += pow(x[i] - 1, 2.0) * (1 + pow(sin(3 * M_PI * x[i + 1]), 2.0));

	return pow(sin(3 * M_PI * x[0]), 2.0) + sum +
		(x[n - 1] - 1) * (1 + pow(sin(2 * M_PI * x[n - 1]), 2.0));
}


/**
 * \brief Matyas Function

* The global minimum is 0,
 * at (0, 0) for n = 2.
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double matyas(const double* x, const int n)
{
	return 0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1];
}

/**
 * \brief Maxmod Function

* The global minimum is 0,
 * at (0, ..., 0).
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double maxmod(const double* x, const int n)
{
	double t = x[0];
	double u = 0.0;
	for (int i = 1; i < n; i++)
	{
		u = fabs(x[i]);
		if (u < t) t = u;
	}
	return u;
}


/**
 * \brief McCormick Function

* The global minimum is -1.9133,
 * at (-0.547, -1.54719).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double mc_cormick(const double* x, const int n)
{
	return sin(x[0] + x[1])
		+ pow(x[0] - x[1], 2.0) - 1.5 * x[0] + 2.5 * x[1] + 1.0;
}


/**
 * \brief Michalewitz Function

 * The global minimum is
 * -0.966n.
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double michalewitz(const double* x, const int n)
{
	double u = 0;
	for (int i = 0; i < n; i++)
	{
		u = u + sin(x[i])
			* pow(sin((i + 1) * x[i] * x[i] / M_PI), 2.0 * 10.0);
	}
	return -u;
}

/**
 * \brief Multimod Function

 * The global minimum is
 * 0 at (0, 0, .., 0).
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double multimod(const double* x, const int n)
{
	double p;
	double s = p = fabs(x[0]);
	for (int i = 1; i < n; i++)
	{
		const double t = fabs(x[1]);
		s += t;
		p *= t;
	}
	return s + p;
}


/**
 * \brief Paviani Function

 * The global minimum is
 * -45.7784 at (9.340266, 9.340266, .., 9.340266).
 * \param x input var
 * \param n dimension, n = 10
 * \return computed result
 */
double paviani(const double* x, const int n)
{
	double sum = 0.0, mul = 1.0;
	for (int i = 0; i < n; i++)
	{
		const double a = log(x[i] - 2.0);
		const double b = log(10.0 - x[i]);
		sum += a * a + b * b;
		mul *= x[i];
	}
	return sum - pow(mul, 0.2);
}

/**
 * \brief plateau Function

 * The global minimum is
 * 30 at (0, 0, 0, 0, 0).
 * \param x input var
 * \param n dimension, n = 5
 * \return computed result
 */
double plateau(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i < 5; i++)
	{
		sum += floor(x[i]);
	}
	return 30.0 + sum;
}


/**
 * \brief Powell Function

 * The global minimum is 
 * 0 at (3, -1, 0, 1,..., 3, -1, 0, 1).
 * \param x input var
 * \param n dimension, n is divisible by 4.
 * \return computed result
 */
double powell(const double* x, const int n)
{
	double sum = 0.0;
	for (int j = 0; j < n / 4; j++)
	{
		sum += (x[4 * j - 3] + 10 * x[4 * j - 2]) * (x[4 * j - 3] + 10 * x[4 * j - 2])
			+ 5 * (x[4 * j - 1] - x[4 * j]) * (x[4 * j - 1] - x[4 * j])
			+ pow(x[4 * j - 2] - 2 * x[4 * j - 1], 4)
			+ 10 * pow(x[4 * j - 3] - x[4 * j], 4);
	}

	return sum;
}


/**
 * \brief Ranna Function

 * \param x input var
 * \param n dimension
 * \return computed result
 */
double rana(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n - 1; i++)
	{
		const double t1 = sqrt(fabs(x[i + 1] + x[i] + 1.0));
		const double t2 = sqrt(fabs(x[i + 1] - x[i] + 1.0));
		sum += (x[i + 1] + 1.0) * cos(t2) * sin(t1) + cos(t1) * sin(t2) * x[i];
	}
	return sum;
}

/**
 * \brief Rastrigin Function

 * \param x input var
 * \param n dimension
 * \return computed result
 */
double rastrigin(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		const double t = x[i];
		sum += t * t - cos(2.0 * M_PI * x[i]);
	}
	return sum + n * 10;
}


/**
 * \brief Rosenbrock saddle function
 *
 * The global minimum is 0 at x_i = −1.0.
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double rosenbrock(const double* x, const int n)
{
	const double a = x[1] - x[0] * x[0];
	const double b = 1.0 - x[0];
	return 100.0 * a * a + b * b;
}

/**
 * \brief Schaffer function
 *
 * The global minimum is 0 at x_i = 0.
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double schaffer(const double* x, const int n)
{
	return pow(x[0] * x[0] + x[1] * x[1], 0.25)
		* (50.0 * pow(x[0] * x[0] + x[1] * x[1], 0.1) + 1.0);
}


/**
 * \brief Schaffer function
 *
 * The global minimum is 0 at x_i = 0.
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double schwefel1_2(const double* x, const int n)
{
	double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		double sum1 = 0.0;
		for (int j = 0; j < i; j++)
		{
			sum1 += x[i];
		}
		sum += sum1 * sum1;
	}
	return sum;
}

/**
 * \brief Schaffer function
 *
 * The global minimum is 0 at x_i = 0.
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double schwefel2_21(const double* x, const int n)
{
	double s = fabs(x[0]);
	for (int i = 1; i < n; i++)
	{
		double t = fabs(x[i]);
		if (t > s)
		{
			s = t;
		}
	}
	return s;
}
