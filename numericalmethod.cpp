#include "numericalmethod.h"

NumericalMethod::NumericalMethod(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N) : f(f), y_exact(y_exact), x_0(x_0), X(X), y_0(y_0), N(N) { }

QVector<QPair<double, double>> NumericalMethod::approximate() const{
    QVector<QPair<double, double>> result(N+1);
    result[0].first = x_0;
    result[0].second = y_0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x_prev = result[i-1].first;
        double y_prev = result[i-1].second;
        double x = x_0 + step*i;
        double y = approximate_next_y(x_prev, y_prev, step, f);
        result[i].first = x;
        result[i].second = y;
    }
    return result;
}

QVector<QPair<double, double>> NumericalMethod::get_local_errors() const {
    QVector<QPair<double, double>> result(N+1);
    result[0].first = x_0;
    result[0].second = 0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x_prev = result[i-1].first;
        double x = x_0 + step*i;
        double error = fabs(y_exact(x, x_0, y_0) - approximate_next_y(x_prev, y_exact(x_prev, x_0, y_0), step, f));
        result[i].first = x;
        result[i].second = error;
    }
    return result;
}

QVector<QPair<double, double>> NumericalMethod::get_global_errors() const {
    QVector<QPair<double, double>> result(N+1);
    auto approximation = approximate();

    result[0].first = x_0;
    result[0].second = 0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x = x_0 + step*i;
        result[i].first = x;
        result[i].second = fabs(y_exact(x, x_0, y_0) - approximation[i].second);
    }
    return result;
}

void NumericalMethod::set_derivative(double (*f)(double, double)) {
    this->f = f;
}

void NumericalMethod::set_exact(double (*y_exact)(double, double, double)) {
    this->y_exact = y_exact;
}

void NumericalMethod::set_x_0(double x_0) {
    this->x_0 = x_0;
}

void NumericalMethod::set_X(double X) {
    this->X = X;
}

void NumericalMethod::set_y_0(double y_0) {
    this->y_0 = y_0;
}

void NumericalMethod::set_N(unsigned int N) {
    this->N = N;
}
