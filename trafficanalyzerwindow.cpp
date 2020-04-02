#include "trafficanalyzerwindow.h"
#include "ui_trafficanalyzerwindow.h"

TrafficAnalyzerWindow::TrafficAnalyzerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrafficAnalyzerWindow)
{
    ui->setupUi(this);
    verticalLayout = new QVBoxLayout(this);
//    verticalBox->setAlignment(Qt::AlignTop);

    //Widgets
    topPanel = new TopPanel(this);
    list = new PacketListVeiw(this);

    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(list->update()));
    timer->start(100);

    QObject::connect(topPanel, SIGNAL(btnStartSniffClicked()),
                     list, SLOT(listUpdate()));

    QObject::connect(topPanel, &TopPanel::btnSettingsSniffClicked,
                     [=] () {
            //Dialog
            captureInterfaces = new CaptureInterfaces();
            captureInterfaces->show();
    });

    QObject::connect(topPanel, SIGNAL(btnStopSniffClicked()), list, SLOT(stopUpdate()));
    QObject::connect(topPanel, SIGNAL(btnRefreshSniffClicked()), list, SLOT(refreshList()));

//    QObject::connect(topPanel, SIGNAL(btnStopSniffClicked()),
//                     list, SLOT(()));
//    QObject::connect(topPanel, &TopPanel::btnSettingsSniffClicked,
//                     [=] () {
//        QDialog *dialog = new QDialog();
//        QHBoxLayout *horizontalLayout = new QHBoxLayout();

//        horizontalLayout->addWidget(captureInterfaces);
//        dialog->setWindowTitle("Settings");
//        dialog->setLayout(horizontalLayout);

//        dialog->show();
//    });
//    QObject::connect(topPanel, SIGNAL(btnRefreshSniffClicked()),
//                     list, SLOT(listUpdate()));


    verticalLayout->addWidget(topPanel);
    verticalLayout->addWidget(list);

    centralWidget()->setLayout(verticalLayout);
}

TrafficAnalyzerWindow::~TrafficAnalyzerWindow()
{
    delete ui;
}

