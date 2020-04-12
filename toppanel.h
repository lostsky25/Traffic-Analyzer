#ifndef TOPPANEL_H
#define TOPPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

class TopPanel : public QWidget
{
    Q_OBJECT
public:
    explicit TopPanel(QWidget *parent = nullptr);
    void setEnabledPanel(bool);
    QPushButton *btnStartSniff;
    QPushButton *btnStopSniff;
    QPushButton *btnSettingsSniff;
    QPushButton *btnRefreshSniff;

public slots:
    void btnStartSniffEvent();
    void btnStopSniffEvent();

private:
    QHBoxLayout *horizontalLayout;
    const int ICON_SIZE = 15;
};

#endif // TOPPANEL_H
