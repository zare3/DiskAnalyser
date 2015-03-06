#ifndef CHECKDISKFRAGMENTATION_H
#define CHECKDISKFRAGMENTATION_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <QRegExp>
#include <QPaintEvent>
#include"nightchart.h"
#include "piechart.h"

namespace Ui {
class CheckDiskFragmentation;
}

class CheckDiskFragmentation : public QDialog
{
    Q_OBJECT

public:
    explicit CheckDiskFragmentation(QWidget *parent = 0);
    QString executeTerminalCmnd(QString cmnd, QStringList args);
    ~CheckDiskFragmentation();

private slots:
    void on_prtitionsCmboBx_currentIndexChanged(const QString &arg1);

private:
    Ui::CheckDiskFragmentation *ui;
    int index;
    PieChart* pieChart;


};

#endif // CHECKDISKFRAGMENTATION_H
