#include "toppanel.h"

TopPanel::TopPanel(QWidget *parent) : QWidget(parent)
{
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setAlignment(Qt::AlignLeft);

    btnStartSniff = new QPushButton(this);
//    btnStartSniff->setIcon(QIcon(":icons/shark_start.png"));
    btnStartSniff->setFixedSize(ICON_SIZE, ICON_SIZE);
    btnStartSniff->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing_or_non_active.png); }");

    btnRefreshSniff = new QPushButton(this);
//    btnStartSniff->setIcon(QIcon("C:/Users/User/Desktop/shark_start.png"));
    btnRefreshSniff->setFixedSize(ICON_SIZE, ICON_SIZE);
    btnRefreshSniff->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    btnRefreshSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing_or_non_active.png); }");

    btnStopSniff = new QPushButton(this);
//    btnStopSniff->setIcon(QIcon("C:/Users/User/Desktop/shark_stop.png"));
    btnStopSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_stop_non_active.png); }");
    btnStopSniff->setFixedSize(ICON_SIZE, ICON_SIZE);
    btnStopSniff->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    btnSettingsSniff = new QPushButton(this);
//    btnSwttingsSniff->setIcon(QIcon("C:/Users/User/Desktop/shark_settings.png"));
    btnSettingsSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_settings.png); }");
    btnSettingsSniff->setFixedSize(ICON_SIZE, ICON_SIZE);
    btnSettingsSniff->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    horizontalLayout->addWidget(btnStartSniff);
    horizontalLayout->addWidget(btnRefreshSniff);
    horizontalLayout->addWidget(btnStopSniff);
    horizontalLayout->addWidget(btnSettingsSniff);

    QObject::connect(btnStartSniff, SIGNAL(clicked()), this, SLOT(btnStartSniffEvent()));
    QObject::connect(btnStopSniff, SIGNAL(clicked()), this, SLOT(btnStopSniffEvent()));
//    QObject::connect(btnRefreshSniff, SIGNAL(clicked()), this, SLOT(btnRefreshSniffEvent()));
//    QObject::connect(btnSettingsSniff, SIGNAL(clicked()), this, SLOT(btnSettingsSniffEvent()));


//    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,900,0);
//    horizontalLayout->setMargin(0);

    setLayout(horizontalLayout);

}

void TopPanel::setEnabledPanel(bool state){
    if(state){
//        btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_start.png); }");
        btnRefreshSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_refresh.png); }");
        btnStopSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_stop.png); }");
        btnStartSniff->setEnabled(true);
        btnStopSniff->setEnabled(true);
        btnRefreshSniff->setEnabled(true);
    }else{
        btnStartSniff->setEnabled(false);
        btnStopSniff->setEnabled(false);
        btnRefreshSniff->setEnabled(false);
    }
}

void TopPanel::btnStartSniffEvent()
{
    btnStartSniff->setEnabled(false);
    btnStopSniff->setEnabled(true);
    btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing_or_non_active.png); }");
    btnStopSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_stop.png); }");
}

void TopPanel::btnStopSniffEvent()
{
    btnStartSniff->setEnabled(true);
    btnStopSniff->setEnabled(false);
    btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_start.png); }");
    btnStopSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_stop_non_active.png); }");
}
