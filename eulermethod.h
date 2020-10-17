#ifndef EULER_METHOD_H
#define EULER_METHOD_H
#include "numericalmethod.h"

class EulerMethod : public NumericalMethod
{
public:
    EulerMethod(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N);

    double approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double)) const;
};

#endif // EULER_METHOD_H
