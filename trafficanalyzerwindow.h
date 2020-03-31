#ifndef TRAFFICANALYZERWINDOW_H
#define TRAFFICANALYZERWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QTimer>
#include <QDebug>

#include "packetlistveiw.h"
#include "toppanel.h"
#include "CaptureInterfaces/captureinterfaces.h"

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
    TopPanel *topPanel;
    PacketListVeiw *list;
    QVBoxLayout *verticalLayout;
    CaptureInterfaces *captureInterfaces;
    QTimer *timer;

};
#endif // TRAFFICANALYZERWINDOW_H
