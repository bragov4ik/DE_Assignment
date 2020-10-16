#ifndef EULER_METHOD_H
#define EULER_METHOD_H
#include "numerical_method.h"

class euler_method : public numerical_method
{
public:
    euler_method(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N);

    double approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double));
};

#endif // EULER_METHOD_H
