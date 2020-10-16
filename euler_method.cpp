#include "euler_method.h"

euler_method::euler_method(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N) : numerical_method(f, y_exact, x_0, X, y_0, N) { }


double euler_method::approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double)) {
    return y_prev + h*f(x_prev, y_prev);
}
