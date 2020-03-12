#include "trafficanalyzerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrafficAnalyzerWindow w;
    w.show();
    return a.exec();
}
