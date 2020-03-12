#ifndef TRAFFICANALYZERWINDOW_H
#define TRAFFICANALYZERWINDOW_H

#include <QMainWindow>
#include "packetlistveiw.h"
#include <QHBoxLayout>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class TrafficAnalyzerWindow; }
QT_END_NAMESPACE

class TrafficAnalyzerWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrafficAnalyzerWindow(QWidget *parent = nullptr);
    ~TrafficAnalyzerWindow();

private:
    Ui::TrafficAnalyzerWindow *ui;
};
#endif // TRAFFICANALYZERWINDOW_H
