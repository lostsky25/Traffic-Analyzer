#include "toppanel.h"
#include <QDebug>

TopPanel::TopPanel(QWidget *parent) : QWidget(parent)
{
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setAlignment(Qt::AlignLeft);

    btnStartSniff = new QPushButton(this);
//    btnStartSniff->setIcon(QIcon("C:/Users/User/Desktop/shark_start.png"));
    btnStartSniff->setFixedSize(ICON_SIZE, ICON_SIZE);
    btnStartSniff->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_start.png); }");

    btnRefreshSniff = new QPushButton(this);
//    btnStartSniff->setIcon(QIcon("C:/Users/User/Desktop/shark_start.png"));
    btnRefreshSniff->setFixedSize(ICON_SIZE, ICON_SIZE);
    btnRefreshSniff->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    btnRefreshSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_refresh.png); }");

    btnStopSniff = new QPushButton(this);
//    btnStopSniff->setIcon(QIcon("C:/Users/User/Desktop/shark_stop.png"));
    btnStopSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_stop.png); }");
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
//    QObject::connect(btnStartSniff, SIGNAL(clicked()), this, SLOT(btnStartSniffEvent()));
//    QObject::connect(btnStartSniff, SIGNAL(clicked()), this, SLOT(btnStartSniffEvent()));
    QObject::connect(btnSettingsSniff, SIGNAL(clicked()), this, SLOT(btnSettingsSniffEvent()));


//    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0,0,900,0);
//    horizontalLayout->setMargin(0);

    setLayout(horizontalLayout);

}

void TopPanel::btnStartSniffEvent()
{
    //qDebug() << __FUNCTION__;
    btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing.png); }");
    emit btnStartSniffClicked();
}

void TopPanel::btnStopSniffEvent()
{
    //btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing.png); }");
    emit btnStopSniffClicked();
}

void TopPanel::btnSettingsSniffEvent()
{
    //btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing.png); }");
    emit btnSettingsSniffClicked();
}

void TopPanel::btnRefreshSniffEvent()
{
    //btnStartSniff->setStyleSheet("QPushButton { border-image: url(C:/Users/User/Desktop/shark_is_runing.png); }");
    emit btnRefreshSniffClicked();
}
