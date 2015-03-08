#ifndef CHECKDISKFRAGMENTATION_H
#define CHECKDISKFRAGMENTATION_H

#include <QDialog>
#include <QProcess>
#include <QDebug>
#include <QRegExp>
#include <QPaintEvent>
#include <QPixmap>
#include<QMovie>
#include "executeTerminalCmndThread.h"
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
    void fragmentationCmndFinished (QString);
    void getDrivesCmndFinished(QString);
    void hideAll ();
    void showLoading();
    void hideLoading();

private:
    Ui::CheckDiskFragmentation *ui;
    int index;
    PieChart* pieChart;
    ExecuteTerminalCmndThread* chkFrgmnThread;
    ExecuteTerminalCmndThread* getPrtitionsThread;
    QString arg1;
    QMovie* spinnerMovie;


};

#endif // CHECKDISKFRAGMENTATION_H
