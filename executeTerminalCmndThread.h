#ifndef CHECKFRAGMENTATIONTHREAD_H
#define CHECKFRAGMENTATIONTHREAD_H

#include <QThread>
#include <QStringList>
#include <QProcess>
#include <QDebug>
class ExecuteTerminalCmndThread : public QThread
{
    Q_OBJECT
public:

    ExecuteTerminalCmndThread(QString , QStringList );
    void run ();

signals:
void cmndFinished(QString );

private :
QStringList args;
QString cmnd;

QString executeTerminalCmnd ();
};

#endif // CHECKFRAGMENTATIONTHREAD_H
