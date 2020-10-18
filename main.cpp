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

    w.show();

    return a.exec();
}
