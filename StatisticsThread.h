#ifndef SSTATISTICSTHREAD_H
#define SSTATISTICSTHREAD_H
#include <QThread>
#include <QFileSystemModel>
#include <QMap>
#include <QVector>

class StatisticsThread : public QThread
{
    Q_OBJECT
    void run();
private:
    QFileSystemModel *fsModel;
    QMap<QModelIndex, quint64> mpSize;
    QMap<QModelIndex, bool> mpHasExec;
    bool done;
    
public:
    StatisticsThread(QFileSystemModel *);
    
    quint64 dirSize(QModelIndex);
    bool hasExec(QModelIndex);
    
    bool isReady() const;
};

#endif // DIRECTORYEXPLORERTHREAD_H
