#include "improvedeulermethod.h"


ImprovedEulerMethod::ImprovedEulerMethod(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N) : NumericalMethod(f, y_exact, x_0, X, y_0, N) { }


double ImprovedEulerMethod::approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double)) const {
    double k1 = f(x_prev, y_prev);
    double k2 = f(x_prev + h, y_prev + h*k1);
    return y_prev + h*(k1+k2)/2;
}
