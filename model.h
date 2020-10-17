#ifndef MODEL_H
#define MODEL_H

#include <QAbstractButton>

// TODO: remove debug things
#include <QDebug>

class Model
{
public:
    explicit Model();


    void set_show_exact(bool value);
    void set_show_euler(bool value);
    void set_show_improved_euler(bool value);
    void set_show_runge_kutta(bool value);

    void set_show_euler_lte(bool value);
    void set_show_improved_euler_lte(bool value);
    void set_show_runge_kutta_lte(bool value);

    void set_show_euler_gte(bool value);
    void set_show_improved_euler_gte(bool value);
    void set_show_runge_kutta_gte(bool value);

    void set_auto_update_graph(bool value);

    void set_n_0(unsigned int value);
    void set_N(unsigned int value);

    void set_x_0(double value);
    void set_y_0(double value);
    void set_X(double value);

private:
    bool show_exact;
    bool show_euler;
    bool show_improved_euler;
    bool show_runge_kutta;

    bool show_euler_lte;
    bool show_improved_euler_lte;
    bool show_runge_kutta_lte;

    bool show_euler_gte;
    bool show_improved_euler_gte;
    bool show_runge_kutta_gte;

    bool auto_update_graph;

    unsigned int n_0;
    unsigned int N;

    double x_0;
    double y_0;
    double X;
};

#endif // MODEL_H
