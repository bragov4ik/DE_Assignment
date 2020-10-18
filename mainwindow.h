#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model.h"

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void on_show_exact_toggled(bool checked);
    void on_show_euler_toggled(bool checked);
    void on_show_improved_euler_toggled(bool checked);
    void on_show_runge_kutta_toggled(bool checked);

    void on_autoupd_checkbox_1_toggled(bool checked);

    void on_n_0_value_changed(unsigned int value);
    void on_N_value_changed(unsigned int value);

    void on_x_0_value_changed(double value);
    void on_y_0_value_changed(double value);
    void on_X_value_changed(double value);

    void on_plot_pushButton_clicked();


private:
    Ui::MainWindow *ui;

    Model model;
};
#endif // MAINWINDOW_H
