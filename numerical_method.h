#ifndef NUMERICAL_METHOD_H
#define NUMERICAL_METHOD_H

#include <QVector>
#include <QPair>
#include <QtMath>

/*!
 * \brief The numerical method class represents a method to approximate differential equations
 *
 * This class has virtual function \c approximate_next_y that is provided by concrete numerical
 * method and \c approximate whose implementation supposed to be the same for all derived classes
 * as all numerical methods used in this assignment work in a similar way.
 */

class numerical_method
{
protected:
    /*!
     * \brief approximate_next_y Finds approximate value of y
     *
     * This function finds approximate value of y at point \c{x_prev+h} using previous values of x and y, step size,
     * and derivative of the function. It is virtual and, hence, unique for each method
     *
     * \param x_prev    Previous value of x
     * \param y_prev    Approximate value of y at point \c x_prev
     * \param h         Step size for approximation
     * \return          Approximated y at point \c{x = x_prev+h}
     */
    virtual double approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double)) = 0;

    double (*f)(double, double);
    double (*y_exact)(double, double, double);
    double x_0;
    double X;
    double y_0;
    unsigned int N;
public:
    /*!
     * \brief numerical_method A method to approximate first order ODE
     *
     * Stores provided values \c{(x_0, X, y_0, N)} and can approximate the differential equation of the
     * form y'=f(x, y) at interval (x_0, X) using \c approximate method as well as find LTE and GTE at
     * each step compared to exact solution \c{y_exact(x, x_0, y_0)}.
     *
     * \param f     Differential equation of the form y'=f(x, y)
     * \param x_0   Initial value of x and start of the interval to approximate
     * \param X     End of the approximation interval (has to be > x_0)
     * \param y_0   Initial value of y at point x_0
     * \param N     Number of steps for approximation
     */
    numerical_method(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N);

    /*!
     * \brief approximate Approximates differential equation
     *
     * Constructs vector of pairs (x, y) based on initial values given before
     *
     * \return      Vector of pairs (x, y) that contains an approximation of given differential equation
     */
    QVector<QPair<double, double>> approximate();

    /*!
     * \brief get_local_errors Evaluate local truncation errors
     *
     * Constructs vector of pairs (x, e) based on initial values given before
     *
     * \return      Vector of pairs (x, e) that contains LTE at each step of approximation
     */
    QVector<QPair<double, double>> get_local_errors();

    /*!
     * \brief get_global_errors Evaluate global truncation errors (GTE)
     *
     * Constructs vector of pairs (x, e) based on initial values given before
     *
     * \return      Vector of pairs (x, e) that contains GTE at each step of approximation
     */
    QVector<QPair<double, double>> get_global_errors();

    void set_derivative(double (*f)(double, double));
    void set_exact(double (*y_exact)(double, double, double));
    void set_x_0(double x_0);
    void set_X(double X);
    void set_y_0(double y_0);
    void set_N(unsigned int N);
};

#endif // NUMERICAL_METHOD_H
