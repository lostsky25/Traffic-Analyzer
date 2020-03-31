#ifndef TOPPANEL_H
#define TOPPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

class TopPanel : public QWidget
{
    Q_OBJECT
public:
    explicit TopPanel(QWidget *parent = nullptr);
    QPushButton *btnStartSniff;
    QPushButton *btnStopSniff;
    QPushButton *btnSettingsSniff;
    QPushButton *btnRefreshSniff;

public slots:
    void btnStartSniffEvent();
    void btnStopSniffEvent();
    void btnSettingsSniffEvent();
    void btnRefreshSniffEvent();

signals:
    void btnStartSniffClicked();
    void btnStopSniffClicked();
    void btnSettingsSniffClicked();
    void btnRefreshSniffClicked();

private:
    QHBoxLayout *horizontalLayout;
    const int ICON_SIZE = 15;
};

#endif // TOPPANEL_H
