#include "executeTerminalCmndThread.h"

ExecuteTerminalCmndThread::ExecuteTerminalCmndThread(QString cmnd, QStringList args)
{
    this->args = args;
    this->cmnd = cmnd;
}

void ExecuteTerminalCmndThread::run()
{
    QString out = executeTerminalCmnd();
    emit cmndFinished(out);
}

QString ExecuteTerminalCmndThread::executeTerminalCmnd()
{
    QProcess OProcess;

    OProcess.start(cmnd,args,QIODevice::ReadOnly); //Starts execution of command
    OProcess.waitForFinished(); //Waits for execution to complete

    QString out = OProcess.readAllStandardOutput(); //Reads standard output
    QString err = OProcess.readAllStandardError(); //Reads standard error

    qDebug()<<"\n Printing the standard output..........\n";
    qDebug()<<out;
    qDebug()<<"\n Printing the standard error..........\n";
    qDebug()<<err;

    return out;
}
