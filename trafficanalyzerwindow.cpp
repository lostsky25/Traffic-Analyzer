#include "trafficanalyzerwindow.h"
#include "ui_trafficanalyzerwindow.h"

TrafficAnalyzerWindow::TrafficAnalyzerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrafficAnalyzerWindow)
{
    ui->setupUi(this);

    //Widgets
    topPanel = new TopPanel(this);
    list = new PacketListVeiw(this);
    verticalLayout = new QVBoxLayout(this);
    selectedDevice = new SelectedDevice(this);
    captureInterfaces = new CaptureInterfaces();

    //Turn off buttons in the top panel
    topPanel->setEnabledPanel(false);

//    QObject::connect(list, SIGNAL(sniffStarted()), topPanel->btnStartSniff, SLOT(clicked()));

    //Top panel signals
    //Buttons
    QObject::connect(topPanel->btnStartSniff, &QPushButton::clicked, [=](){list->startSniff(lastDeviceName);});         //Start
    QObject::connect(topPanel->btnStopSniff, &QPushButton::clicked, list, &PacketListVeiw::stopUpdate);                 //Stop
    QObject::connect(topPanel->btnRefreshSniff, &QPushButton::clicked, list, &PacketListVeiw::refreshList);             //Refresh
    QObject::connect(topPanel->btnSettingsSniff, &QPushButton::clicked, captureInterfaces, &CaptureInterfaces::show);   //Settings
    //!Buttons

    //If monitoring is in proccess, then hide SelectedDevice (QWidget)
    QObject::connect(list, &PacketListVeiw::sniffStarted, selectedDevice, &SelectedDevice::hide);

    //If we chose some device, then active buttons
    QObject::connect(selectedDevice->getTable(), &QTableWidget::itemDoubleClicked, [=](){
        topPanel->setEnabledPanel(true);
    });

    //Save last device name
    QObject::connect(list, &PacketListVeiw::lastDeviceName, [=](QTableWidgetItem *devName){
        lastDeviceName = devName;
    });

    //Start sniff with last device name or first (from table)
    QObject::connect(selectedDevice->getTable(), SIGNAL(itemDoubleClicked(QTableWidgetItem *)), list, SLOT(startSniff(QTableWidgetItem *)));


    //In Input tab
//    QObject::connect(captureInterfaces->input->getTable(), &QTableWidget::itemDoubleClicked, list, &PacketListVeiw::listUpdate);
    QObject::connect(captureInterfaces->input->getTable(), &QTableWidget::itemDoubleClicked, topPanel, &TopPanel::setEnabledPanel);
//    QObject::connect(captureInterfaces->input->getTable(), SIGNAL(itemDoubleClicked(QTableWidgetItem *)), list, SLOT(startSniff(QTableWidgetItem *)));

//    QObject::connect(captureInterfaces->input->getTable(), SIGNAL(itemDoubleClicked(QTableWidgetItem *)), list, SLOT(foo(QTableWidgetItem *)));

    QObject::connect(captureInterfaces->input->getTable(), &QTableWidget::itemDoubleClicked, captureInterfaces, &QDialog::close);
//    QObject::connect(captureInterfaces->input->getTable(), &QTableWidget::itemDoubleClicked, [=] (QTableWidgetItem *devName){
//        lastDeviceName = devName;
//    });

    //!In Input tab

    QObject::connect(captureInterfaces, &QDialog::finished, list, &PacketListVeiw::stopUpdate);


    selectedDevice->addDevice(list->getDeviceNames());
    captureInterfaces->input->addDevice(list->getDeviceNames());

    verticalLayout->setSpacing(0);
    verticalLayout->setMargin(0);
    verticalLayout->setContentsMargins(0, 6, 0, 6);

    topPanel->setContentsMargins(6, 0, 9, 0);
    selectedDevice->setContentsMargins(0, 0, 0, 0);

    verticalLayout->addWidget(topPanel);
    verticalLayout->addWidget(list);
    verticalLayout->addWidget(selectedDevice);

    centralWidget()->setLayout(verticalLayout);
}

TrafficAnalyzerWindow::~TrafficAnalyzerWindow()
{
    delete ui;
}

