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
#endif
