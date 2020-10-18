#include "model.h"

Model::Model() {
    methods_chart = new QChart();

    exact_series = new QLineSeries();
    euler_series = new QLineSeries();
    improved_euler_series = new QLineSeries();
    runge_kutta_series = new QLineSeries();

    methods_chart->createDefaultAxes();
    methods_chart->setTitle(METHODS_GRAPH_NAME);

    methods_chart->addSeries(exact_series);
    methods_chart->addSeries(euler_series);
    methods_chart->addSeries(improved_euler_series);
    methods_chart->addSeries(runge_kutta_series);
    for(auto now: methods_chart->legend()->markers()) {
        QString a("");
        now->setLabel(a);
    }

    // LTE graphs
    lte_chart = new QChart();

    euler_lte_series = new QLineSeries();
    improved_euler_lte_series = new QLineSeries();
    runge_kutta_lte_series = new QLineSeries();

    lte_chart->legend()->hide();
    lte_chart->createDefaultAxes();
    lte_chart->setTitle(LTE_GRAPH_NAME);

    lte_chart->addSeries(euler_lte_series);
    lte_chart->addSeries(improved_euler_lte_series);
    lte_chart->addSeries(runge_kutta_lte_series);
    for(auto now: lte_chart->legend()->markers()) {
        QString a("");
        now->setLabel(a);
    }

    // GTE graphs
    gte_chart = new QChart();

    euler_gte_series = new QLineSeries();
    improved_euler_gte_series = new QLineSeries();
    runge_kutta_gte_series = new QLineSeries();

    gte_chart->legend()->hide();
    gte_chart->createDefaultAxes();
    gte_chart->setTitle(GTE_GRAPH_NAME);

    gte_chart->addSeries(euler_gte_series);
    gte_chart->addSeries(improved_euler_gte_series);
    gte_chart->addSeries(runge_kutta_gte_series);
    for(auto now: gte_chart->legend()->markers()) {
        QString a("");
        now->setLabel(a);
    }
    update_all_graphs();
}

double Model::derivative(double x, double y)
{
    return DERIVATIVE;
}

double Model::exact(double x, double x_0, double y_0)
{
    return EXACT;
}

void Model::set_show_exact(bool value)
{
    show_exact = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_show_euler(bool value)
{
    show_euler = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_show_improved_euler(bool value)
{
    show_improved_euler = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_show_runge_kutta(bool value)
{
    show_runge_kutta = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_auto_update_graph(bool value)
{
    auto_update_graph = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_n_0(unsigned int value)
{
    n_0 = value;
    if (auto_update_graph) {
        update_gte_graph();
    }
}

void Model::set_N(unsigned int value)
{
    N = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_x_0(double value)
{
    if (value != 0) {
        x_0 = value;
        if (auto_update_graph) {
            update_all_graphs();
        }
    }
}

void Model::set_y_0(double value)
{
    y_0 = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::set_X(double value)
{
    X = value;
    if (auto_update_graph) {
        update_all_graphs();
    }
}

void Model::update_methods_graph()
{
    update_line_series<EulerMethod>(exact_series, &NumericalMethod::get_exact, methods_chart, show_exact);
    update_line_series<EulerMethod>(euler_series, &NumericalMethod::approximate, methods_chart, show_euler);
    update_line_series<ImprovedEulerMethod>(improved_euler_series, &NumericalMethod::approximate, methods_chart, show_improved_euler);
    update_line_series<RungeKuttaMethod>(runge_kutta_series, &NumericalMethod::approximate, methods_chart, show_runge_kutta);

    QVector<QLineSeries*> series_vect {exact_series, euler_series, improved_euler_series, runge_kutta_series};
    QVector<QString> names_vect {"Exact", "Euler", "Improved Euler", "Runge-Kutta"};
    for(int i = 0; i < series_vect.size(); i++) {
        if(!methods_chart->legend()->markers(series_vect[i]).empty()) {
            methods_chart->legend()->markers(series_vect[i])[0]->setLabel(names_vect[i]);
        }
    }
    methods_chart->createDefaultAxes();
    return;
}

void Model::update_lte_graph()
{
    update_line_series<EulerMethod>(euler_lte_series, &NumericalMethod::get_local_errors, lte_chart, show_euler);
    update_line_series<ImprovedEulerMethod>(improved_euler_lte_series, &NumericalMethod::get_local_errors, lte_chart, show_improved_euler);
    update_line_series<RungeKuttaMethod>(runge_kutta_lte_series, &NumericalMethod::get_local_errors, lte_chart, show_runge_kutta);

    QVector<QLineSeries*> series_vect {euler_lte_series, improved_euler_lte_series, runge_kutta_lte_series};
    QVector<QString> names_vect {"Euler", "Improved Euler", "Runge-Kutta"};
    for(int i = 0; i < series_vect.size(); i++) {
        if(!lte_chart->legend()->markers(series_vect[i]).empty()) {
            lte_chart->legend()->markers(series_vect[i])[0]->setLabel(names_vect[i]);
        }
    }
    lte_chart->createDefaultAxes();
    return;
}

void Model::update_gte_graph()
{
    update_line_series<EulerMethod>(euler_gte_series, &NumericalMethod::get_max_global_errors, gte_chart, show_euler);
    update_line_series<ImprovedEulerMethod>(improved_euler_gte_series, &NumericalMethod::get_max_global_errors, gte_chart, show_improved_euler);
    update_line_series<RungeKuttaMethod>(runge_kutta_gte_series, &NumericalMethod::get_max_global_errors, gte_chart, show_runge_kutta);

    QVector<QLineSeries*> series_vect {euler_gte_series, improved_euler_gte_series, runge_kutta_gte_series};
    QVector<QString> names_vect {"Euler", "Improved Euler", "Runge-Kutta"};
    for(int i = 0; i < series_vect.size(); i++) {
        if(!gte_chart->legend()->markers(series_vect[i]).empty()) {
            gte_chart->legend()->markers(series_vect[i])[0]->setLabel(names_vect[i]);
        }
    }
    gte_chart->createDefaultAxes();
    return;
}

void Model::update_all_graphs()
{
    update_methods_graph();
    update_lte_graph();
    update_gte_graph();
    return;
}

QChart *Model::get_methods_chart() const
{
    return methods_chart;
}

QChart *Model::get_lte_chart() const
{
    return lte_chart;
}

QChart *Model::get_gte_chart() const
{
    return gte_chart;
}

template<class MethodClass>
void Model::update_line_series(QLineSeries *series, QVector<QPointF> (NumericalMethod::*producer)(void) const, QChart* chart, bool show_method)
{
    if (show_method) {
        MethodClass method_instance(
                    [](double x, double y) { return DERIVATIVE; }
                    , [](double x, double x_0, double y_0) { return EXACT; }
                    , x_0, X, y_0, N);
        series->replace( ( ( static_cast<NumericalMethod*>(&method_instance) )->*producer )() );
        // update the series in the chart
        chart->removeSeries(series);
        chart->addSeries(series);
    }
    else {
        chart->removeSeries(series);
    }
    return;
}


template<class MethodClass>
void Model::update_line_series(QLineSeries *series, QVector<QPointF> (NumericalMethod::*producer)(unsigned int), QChart *chart, bool show_method)
{
    if (show_method) {
        MethodClass method_instance(
                    [](double x, double y) { return DERIVATIVE; }
                    , [](double x, double x_0, double y_0) { return EXACT; }
                    , x_0, X, y_0, N);
        series->replace( ( ( static_cast<NumericalMethod*>(&method_instance) )->*producer )(n_0) );
        // update the series in the chart
        chart->removeSeries(series);
        chart->addSeries(series);
    }
    else {
        chart->removeSeries(series);
    }
    return;
}
