#include "trafficanalyzerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrafficAnalyzerWindow w;
    //Fixed minimum size of frame
    w.setMinimumSize(QSize(1300, 500));

    w.show();
    return a.exec();
}
