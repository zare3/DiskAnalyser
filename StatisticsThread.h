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
public:
    class ExtStat{
    public:
        QMap<QString, quint64> nExt;
    };

private:
    QFileSystemModel *fsModel;
    QMap<QModelIndex, quint64> mpSize;
    QMap<QModelIndex, quint64> mpNExec;
    QMap<QModelIndex, ExtStat> mpExt;
    bool done;
    QFileInfoList fiLExec;
public:
    StatisticsThread(QFileSystemModel *);
    
    //quint64 dirSize(const QString &);
    quint64 dirSize(QModelIndex);
    quint64 nExec(QModelIndex);
    QFileInfoList* lExec();
    void lExecClear();
    const ExtStat* const getExt(QModelIndex);
    
    bool isReady() const;
};

#endif // DIRECTORYEXPLORERTHREAD_H
