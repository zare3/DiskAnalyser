#ifndef CHECKSECURITYTHREATS_H
#define CHECKSECURITYTHREATS_H

#include <QDialog>
#include <QStandardItemModel>
#include <QWidgetItem>
#include <QTableWidgetItem>
#include <QDebug>
#include "StatisticsThread.h"

namespace Ui {
class CheckSecurityThreats;
}

class CheckSecurityThreats : public QDialog
{
    Q_OBJECT

public:
    explicit CheckSecurityThreats(QFileSystemModel*, StatisticsThread*, QWidget *parent = 0);
    ~CheckSecurityThreats();

private:
    Ui::CheckSecurityThreats *ui;
    QStandardItemModel *model;
    StatisticsThread* ststicsThread;
    quint64 nExecutables;
    QFileInfoList* execList;
    QFileSystemModel* Sysmodel;

};

#endif // CHECKSECURITYTHREATS_H
