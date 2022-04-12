#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H


/**
 * \brief Ackley function
 *
 * It has a global minimum 0 at x_i = 0.
 * \param x input var
 * \param n the dimension of input
 * \return computed result
 */
double ackley(const double* x, const int n);

/**
 * \brief Beale function
 *
 * a two-dimensional function, The global minimum is 0
 * at (3, 0.5).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double beale(const double* x, const int n);

/**
 * \brief Bohachevsky function
 *
 * A two-dimensional function, The global minimum is 0
 * at (0, 0).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double bohachevsky(const double* x, const int n);

/**
 * \brief Booth function
 *
 * A two-dimensional function, The global minimum is 0
 * at (1, 3).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double booth(const double* x, const int n);

/**
 * \brief Box-Betts function
 *
 * A three-dimensional function. The global minimum is 0
 * at (1, 10, 1).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double box_betts(const double* x, const int n);

/**
 * \brief Branin function
 *
 * It has a global minimum function value of 0.398
 * at the points (−3.142, 12.275), (3.142, 2.275) and (9.425, 2.425).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double branin(const double* x, const int n);

/**
 * \brief Camel function
 * A two-dimensional function, The global minimum is 0
 * at (0, 0).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double camel3(const double* x, const int n);

/**
 * \brief Chichinadze function
 * A two-dimensional function, The global minimum is 43.3159
 * at  (5.90133, 0.5).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double chichinadze(const double* x, const int n);

/**
 * \brief Cola function
 * A 17-dimensional function, The global minimum is 11.7464.
 * \param x input var
 * \param n dimension, n = 17
 * \return computed result
 */
double cola(const double* x, const int n);

/**
 * \brief Colville function
 * A 4-dimensional function, The global minimum is 0,
 * at the point(1, 1, 1, 1).
 * \param x input var
 * \param n dimension, n = 4
 * \return computed result
 */
double colville(const double* x, const int n);

/**
 * \brief Corana function
 * A 4-dimensional function, The global minimum is 0.
 * \param x input var
 * \param n dimension, n = 4
 * \return computed result
 */
double corana(const double* x, const int n);

/**
 * \brief Easom function
 * A 2-dimensional function, The global minimum is -1,
 * at point (-pi, pi).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double easom(const double* x, const int n);

/**
 * \brief Egg holder function
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double eggholder(const double* x, const int n);

/**
 * \brief Gear function
 *
 * A 4-dimensional function, The global minimum is 2.7e-12,
 * at (16, 19, 43, 49).
 * \param x input var
 * \param n dimension, n = 4
 * \return computed result
 */
double gear(const double* x, const int n);


/**
 * \brief GoldsteinPrice function
 *
 * A 2-dimensional function, The global minimum is 3,
 * at (0, -1).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double goldstein_price(const double* x, const int n);

/**
 * \brief Griewank function
 *
 * A 2-dimensional function, The global minimum is 0,
 * at (0, 0).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double griewank(const double* x, const int n);


/**
 * \brief Hansen function
 *
 * A 2-dimensional function, The global minimum is -176.54,.
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double hansen(const double* x, const int n);


/**
 * \brief Hartman function
 *
 * The global minimum is − 3:86,
 * at (0.114, 0.556, 0.852).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double hartman3(const double* x, const int n = 3);


/**
 * \brief Hartman function
 *
 * The global minimum is -3.32,
 * at (0.201, 0.150, 0.477, 0.275, 0.311, 0.657).
 * \param x input var
 * \param n dimension, n = 6
 * \return computed result
 */
double hartman6(const double* x, const int n = 6);


/**
 * \brief Himmelblau function
 *
 * The global minimum is 0,
 * at (3, 2).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double himmelblau(const double* x, const int n);

/**
 * \brief Holzman function
 *
 * The global minimum is 0,
 * at (50, 25, 1.5).
 * \param x input var
 * \param n dimension, n = 3
 * \return computed result
 */
double holzman1(const double* x, const int n);


/**
 * \brief Holzman function
 *
 * The global minimum is 0,
 * at (0, ..., 0).
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double holzman2(const double* x, const int n);


/**
 * \brief Hosaki function
 *
 * The global minimum is -2.3458,
 * at (4, 2).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double hosaki(const double* x, const int n);

/**
 * \brief Katsuuras function
 *
 * The global minimum is 0,
 * at (0,...,0).
 * \param x input var
 * \param n dimension, n = 10
 * \return computed result
 */
double katsuuras(const double* x, const int n);

/**
 * \brief Lennard-Jones function
 *
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double lennard_jones(const double* x, const int n);

/**
 * \brief Leon function
 *
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double leon(const double* x, const int n);


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
double levy(const double* x, const int n);


/**
 * \brief Matyas Function

* The global minimum is 0,
 * at (0, 0) for n = 2.
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double matyas(const double* x, const int n);


/**
 * \brief Maxmod Function

* The global minimum is 0,
 * at (0, ..., 0).
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double maxmod(const double* x, const int n);

/**
 * \brief McCormick Function

* The global minimum is -1.9133,
 * at (-0.547, -1.54719).
 * \param x input var
 * \param n dimension, n = 2
 * \return computed result
 */
double mc_cormick(const double* x, const int n);

/**
 * \brief Michalewitz Function

 * The global minimum is .
 * -0.966n.
 * \param x input var
 * \param n dimension
 * \return computed result
 */
double michalewitz(const double* x, const int n);
#endif
