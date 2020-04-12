#ifndef INPUT_H
#define INPUT_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

class Input : public QWidget
{
    Q_OBJECT
public:
    explicit Input(QWidget *parent = nullptr);
    void addDevice(const QStringList &);
    QTableWidget *getTable();

private:
    QTableWidget *table;
    QVBoxLayout *verticalLayout;

protected:
    int row, column;
};

#endif // INPUT_H
