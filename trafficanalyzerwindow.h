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
    TopPanel *topPanel;
    PacketListVeiw *list;
    QTableWidgetItem *lastDeviceName;
    QVBoxLayout *verticalLayout;
    Ui::TrafficAnalyzerWindow *ui;
    SelectedDevice *selectedDevice;
    CaptureInterfaces *captureInterfaces;
};
#endif // TRAFFICANALYZERWINDOW_H
