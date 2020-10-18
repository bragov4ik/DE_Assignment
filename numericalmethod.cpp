#include "numericalmethod.h"

NumericalMethod::NumericalMethod(double (*f)(double, double), double (*y_exact)(double, double, double), double x_0, double X, double y_0, unsigned int N) : f(f), y_exact(y_exact), x_0(x_0), X(X), y_0(y_0), N(N) { }

QVector<QPointF> NumericalMethod::approximate() const{
    QVector<QPointF> result(N+1);
    // WARNING: may be problems with points not initialized
    result[0].rx() = x_0;
    result[0].ry() = y_0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x_prev = result[i-1].rx();
        double y_prev = result[i-1].ry();
        double x = x_0 + step*i;
        double y = approximate_next_y(x_prev, y_prev, step, f);
        result[i].rx() = x;
        result[i].ry() = y;
    }
    return result;
}

QVector<QPointF> NumericalMethod::get_local_errors() const {
    QVector<QPointF> result(N+1);
    result[0].rx() = x_0;
    result[0].ry() = 0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x_prev = result[i-1].rx();
        double x = x_0 + step*i;
        double error = fabs(y_exact(x, x_0, y_0) - approximate_next_y(x_prev, y_exact(x_prev, x_0, y_0), step, f));
        result[i].rx() = x;
        result[i].ry() = error;
    }
    return result;
}

QVector<QPointF> NumericalMethod::get_max_global_errors(unsigned int n_0)
{
    // use N_orig as N will change within the method
    // keep original value of N to restore it later
    unsigned int N_orig = N;

    QVector<QPointF> result(N_orig - n_0 + 1);
    for (unsigned int i = n_0; i <= N_orig; i++) {
        N = i;
        result[i-n_0].rx() = i;
        result[i-n_0].ry() = get_max_global_error();
    }

    N = N_orig;
    return result;
}

double NumericalMethod::get_max_global_error() const {
    auto approximation = approximate();

    double max_error = 0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x = x_0 + step*i;
        double error = fabs(y_exact(x, x_0, y_0) - approximation[i].ry());
        if (error > max_error) {
            max_error = error;
        }
    }
    return max_error;
}

QVector<QPointF> NumericalMethod::get_exact() const
{
    QVector<QPointF> result(N+1);
    // WARNING: may be problems with points not initialized
    result[0].rx() = x_0;
    result[0].ry() = y_0;
    double step = (X - x_0)/N;
    for (unsigned int i = 1; i < N+1; i++) {
        double x = x_0 + step*i;
        double y = y_exact(x, x_0, y_0);
        result[i].rx() = x;
        result[i].ry() = y;
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
