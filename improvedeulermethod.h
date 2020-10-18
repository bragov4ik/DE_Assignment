#ifndef IMPROVEDEULERMETHOD_H
#define IMPROVEDEULERMETHOD_H

#include "numericalmethod.h"

class ImprovedEulerMethod : public NumericalMethod
{
public:
    ImprovedEulerMethod(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N);

    double approximate_next_y(double x_prev, double y_prev, double h, double (*f)(double, double)) const;
};

#endif // IMPROVEDEULERMETHOD_H
