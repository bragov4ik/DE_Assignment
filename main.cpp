#include "mainwindow.h"
#include "model.h"

#include <QApplication>
#include <QtCharts>
#include <QObject>

using namespace QtCharts;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    MainWindow w;

    // TODO: delete this, only trying to do something
    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Hahah funny title (no)");

    QGridLayout* grid_layout = w.findChild<QGridLayout*>("gridLayout");
    Q_ASSERT(grid_layout);
    QChartView* graphics_view = w.findChild<QChartView*>("graphicsView_approx");
    Q_ASSERT(graphics_view);
    graphics_view->setChart(chart);
    graphics_view->setRenderHint(QPainter::HighQualityAntialiasing);
    // delete up to this

    Model model;

    QButtonGroup* buttonGroup_methods = w.findChild<QButtonGroup*>("buttonGroup_methods");
    w.show();

    return a.exec();
}
