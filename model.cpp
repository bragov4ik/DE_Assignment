#include "model.h"

Model::Model() { }

void Model::set_show_exact(bool value)
{
    show_exact = value;
}

void Model::set_show_euler(bool value)
{
    show_euler = value;
}

void Model::set_show_improved_euler(bool value)
{
    show_improved_euler = value;
}

void Model::set_show_runge_kutta(bool value)
{
    show_runge_kutta = value;
}

void Model::set_show_euler_lte(bool value)
{
    show_euler_lte = value;
}

void Model::set_show_improved_euler_lte(bool value)
{
    show_improved_euler_lte = value;
}

void Model::set_show_runge_kutta_lte(bool value)
{
    show_runge_kutta_lte = value;
}

void Model::set_show_euler_gte(bool value)
{
    show_euler_gte = value;
}

void Model::set_show_improved_euler_gte(bool value)
{
    show_improved_euler_gte = value;
}

void Model::set_show_runge_kutta_gte(bool value)
{
    show_runge_kutta_gte = value;
}

void Model::set_auto_update_graph(bool value)
{
    auto_update_graph = value;
}

void Model::set_n_0(unsigned int value)
{
    n_0 = value;
}

void Model::set_N(unsigned int value)
{
    N = value;
}

void Model::set_x_0(double value)
{
    x_0 = value;
}

void Model::set_y_0(double value)
{
    y_0 = value;
}

void Model::set_X(double value)
{
    X = value;
}
