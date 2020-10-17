#include "eulermethod.h"

EulerMethod::EulerMethod(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N) : NumericalMethod(f, y_exact, x_0, X, y_0, N) { }


double EulerMethod::approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double)) const {
    return y_prev + h*f(x_prev, y_prev);
}
