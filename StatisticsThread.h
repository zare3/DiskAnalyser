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
    QMap<QModelIndex, quint64> mpNExec;
    bool done;
    QFileInfoList fiLExec;
public:
    StatisticsThread(QFileSystemModel *);
    
    //quint64 dirSize(const QString &);
    quint64 dirSize(QModelIndex);
    quint64 nExec(QModelIndex);
    QFileInfoList* lExec();
    void lExecClear();
    bool isReady() const;
};

#endif // DIRECTORYEXPLORERTHREAD_H
