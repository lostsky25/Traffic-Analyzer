#include "captureinterfaces.h"

CaptureInterfaces::CaptureInterfaces(QWidget *parent) : QDialog(parent)
{
    this->setMinimumSize(950, 470);
    this->setWindowTitle("Traffic Analyzer ~ Capture Interfaces");

    horizontalLayout = new QHBoxLayout(this);
    tabWidget = new QTabWidget(this);
    input = new Input(this);

    tabWidget->addTab(input, tr("Input"));
    tabWidget->addTab(new Output(), tr("Output"));
    tabWidget->addTab(new Options(), tr("Options"));


    tabWidget->setContentsMargins(10, 50, 40, 10);
    tabWidget->setMinimumSize(900, 300);

    horizontalLayout->setAlignment(Qt::AlignCenter);

    horizontalLayout->addWidget(tabWidget);
    setLayout(horizontalLayout);
}

CaptureInterfaces::~CaptureInterfaces()
{

}
