#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model()
{
    ui->setupUi(this);

    QObject::connect(ui->checkBox_exact, &QAbstractButton::toggled, this, &MainWindow::on_show_exact_toggled);
    QObject::connect(ui->checkBox_euler, &QAbstractButton::toggled, this, &MainWindow::on_show_euler_toggled);
    QObject::connect(ui->checkBox_improved_euler, &QAbstractButton::toggled, this, &MainWindow::on_show_improved_euler_toggled);
    QObject::connect(ui->checkBox_runge_kutta, &QAbstractButton::toggled, this, &MainWindow::on_show_runge_kutta_toggled);

    QObject::connect(ui->autoupd_checkbox_1, &QAbstractButton::toggled, this, &MainWindow::on_autoupd_checkbox_1_toggled);

    QObject::connect(ui->ivalue_spinBox_6, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_n_0_value_changed);
    QObject::connect(ui->ivalue_spinBox_5, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::on_N_value_changed);

    QObject::connect(ui->ivalue_doubleSpinBox_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_x_0_value_changed);
    QObject::connect(ui->ivalue_doubleSpinBox_3, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_y_0_value_changed);
    QObject::connect(ui->ivalue_doubleSpinBox_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::on_X_value_changed);

    QObject::connect(ui->plot_pushButton, &QAbstractButton::clicked, this, &MainWindow::on_plot_pushButton_clicked);
    QObject::connect(ui->plot_pushButton_2, &QAbstractButton::clicked, this, &MainWindow::on_plot_pushButton_clicked);

    QChartView* methods_view = ui->graphicsView_approx;
    methods_view->setChart(model.get_methods_chart());
    methods_view->setRenderHint(QPainter::HighQualityAntialiasing);

    QChartView* lte_view = ui->graphicsView_lte;
    lte_view->setChart(model.get_lte_chart());
    lte_view->setRenderHint(QPainter::HighQualityAntialiasing);

    QChartView* gte_view = ui->graphicsView_gte;
    gte_view->setChart(model.get_gte_chart());
    gte_view->setRenderHint(QPainter::HighQualityAntialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_show_exact_toggled(bool checked)
{
    model.set_show_exact(checked);
}
void MainWindow::on_show_euler_toggled(bool checked)
{
    model.set_show_euler(checked);
}
void MainWindow::on_show_improved_euler_toggled(bool checked)
{
    model.set_show_improved_euler(checked);
}

void MainWindow::on_show_runge_kutta_toggled(bool checked)
{
    model.set_show_runge_kutta(checked);
}

void MainWindow::on_autoupd_checkbox_1_toggled(bool checked)
{
    model.set_auto_update_graph(checked);
}

void MainWindow::on_n_0_value_changed(unsigned int value)
{
    model.set_n_0(value);

    // we want to keep the n_0 value <= N
    unsigned int N = ui->ivalue_spinBox_5->value();
    if (value > N) {
        ui->ivalue_spinBox_5->setValue(value);
    }
}

void MainWindow::on_N_value_changed(unsigned int value)
{
    model.set_N(value);

    // we want to keep the n_0 value <= N
    unsigned int n_0 = ui->ivalue_spinBox_6->value();
    if (n_0 > value) {
        ui->ivalue_spinBox_6->setValue(value);
    }
}


void MainWindow::on_x_0_value_changed(double value)
{
    if (value == 0) {
        QMessageBox::critical(
                    this,
                    "Error!",
                    "Division by 0: x_0 cannot be 0!");
    }
    else {
        model.set_x_0(value);

        // we want to keep the x_0 value <= X
        double X = ui->ivalue_doubleSpinBox_2->value();
        if (value > X) {
            ui->ivalue_doubleSpinBox_2->setValue(value);
        }
    }
}

void MainWindow::on_y_0_value_changed(double value)
{
    model.set_y_0(value);
}

void MainWindow::on_X_value_changed(double value)
{
    model.set_X(value);

    // we want to keep the x_0 value <= X
    double x_0 = ui->ivalue_doubleSpinBox_1->value();
    if (x_0 > value) {
        ui->ivalue_doubleSpinBox_1->setValue(value);
    }
}

void MainWindow::on_plot_pushButton_clicked()
{
    model.update_all_graphs();
}
