#ifndef MODEL_H
#define MODEL_H

// derivative function in c++ syntax in terms of x and y variables
// I put ridiculously big number as when x approaches 0 the derivative goes to infty
#define DERIVATIVE (x==0 ? 9000000000000000 : (2*x*x*x+2*y/x))

// exact solution function in c++ syntax in terms of y, x_0, and y_0 variables
#define EXACT (x*x*(x*x + y_0/(x_0*x_0) - x_0*x_0))

#define METHODS_GRAPH_NAME "Approximations"
#define LTE_GRAPH_NAME "Local errors"
#define GTE_GRAPH_NAME "Global errors"

#include "numericalmethod.h"
#include "eulermethod.h"
#include "improvedeulermethod.h"
#include "rungekuttamethod.h"

#include <QAbstractButton>
#include <QtCharts>
// TODO: remove
#include <QtDebug>

class Model
{
public:
    explicit Model();

    /*!
     * \brief derivative computes derivative y'=f(x, y) of function to solve
     * \param x x - argument of f
     * \param y y - argument of f
     */
    double derivative(double x, double y);

    /*!
     * \brief exact computes value of analytical solution at point x
     * \param x
     * \param x_0
     * \param y_0
     * \return
     */
    double exact(double x, double x_0, double y_0);

    void set_show_exact(bool value);
    void set_show_euler(bool value);
    void set_show_improved_euler(bool value);
    void set_show_runge_kutta(bool value);

    void set_auto_update_graph(bool value);

    void set_n_0(unsigned int value);
    void set_N(unsigned int value);

    void set_x_0(double value);
    void set_y_0(double value);
    void set_X(double value);

    /*!
     * \brief update_methods_graph update QChartView of approximation graphs
     */
    void update_methods_graph();

    /*!
     * \brief update_lte_graph update QChartView of lte graphs
     */
    void update_lte_graph();

    /*!
     * \brief update_gte_graph update QChartView of gte graphs
     */
    void update_gte_graph();

    /*!
     * \brief update_all_graphs update QChartView of all graphs
     */
    void update_all_graphs();

    QChart *get_methods_chart() const;

    QChart *get_lte_chart() const;

    QChart *get_gte_chart() const;

private:

    template<class MethodClass>
    void update_line_series(QLineSeries *series, QVector<QPointF> (NumericalMethod::*producer)(void) const, QChart* chart, bool show_method);

    template<class MethodClass>
    void update_line_series(QLineSeries *series, QVector<QPointF> (NumericalMethod::*producer)(unsigned int), QChart* chart, bool show_method);

    bool show_exact = 1;
    bool show_euler = 1;
    bool show_improved_euler = 1;
    bool show_runge_kutta = 1;

    /*!
     * \brief auto_update_graph indicates whether updates of graphs should be called on update of corresponding fields
     */
    bool auto_update_graph = 0;

    unsigned int n_0 = 1;
    unsigned int N = 10;

    double x_0 = 1;
    double y_0 = 2;
    double X = 10;

    // Approximations
    QChart* methods_chart;

    QLineSeries* exact_series;
    QLineSeries* euler_series;
    QLineSeries* improved_euler_series;
    QLineSeries* runge_kutta_series;

    // LTE graphs
    QChart* lte_chart;

    QLineSeries* euler_lte_series;
    QLineSeries* improved_euler_lte_series;
    QLineSeries* runge_kutta_lte_series;

    // GTE graphs
    QChart* gte_chart;

    QLineSeries* euler_gte_series;
    QLineSeries* improved_euler_gte_series;
    QLineSeries* runge_kutta_gte_series;
};

#endif // MODEL_H
