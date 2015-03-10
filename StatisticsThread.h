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
    class OwnStat{
    public:
        QMap<QString, quint64> nOwn;
    } OwnRet;   //Hack to solve null pointer issue till fixed properly
    class GroupStat{
    public:
        QMap<QString, quint64> nGroup;
    } GroupRet;  //Hack to solve null pointer issue till fixed properly

private:
    QFileSystemModel *fsModel;
    QMap<QModelIndex, quint64> mpSize;
    QMap<QModelIndex, quint64> mpNExec;
    QMap<QModelIndex, ExtStat> mpExt;
    QMap<QModelIndex, OwnStat> mpOwn;
    QMap<QModelIndex, GroupStat> mpGroup;
    
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
    const OwnStat* const getOwn(QModelIndex);
    const GroupStat* const getGroup(QModelIndex);
    bool isReady() const;
};

#endif // DIRECTORYEXPLORERTHREAD_H
