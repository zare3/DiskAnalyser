#ifndef SSTATISTICSTHREAD_H
#define SSTATISTICSTHREAD_H
#include <QThread>
#include <QFileSystemModel>
#include <QMap>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QQueue>
#define MAX_DEPTH 4

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
    QMap<QModelIndex, quint64> mpfileCount;
    QMap<QModelIndex, quint64> mpNExec;
    QMap<QModelIndex, ExtStat> mpExt;
    QMap<QModelIndex, OwnStat> mpOwn;
    QMap<QModelIndex, GroupStat> mpGroup;
    QFileInfoList fiLExec;
    
private:
    bool running;
    enum runID_t{ID_IDEL, ID_getJson, ID_dirSize, ID_fileCount, ID_nExec, ID_getExt, ID_getOwn, ID_getGroup};
    QQueue<QPair<QModelIndex, runID_t> > Q;
public:
    //QJsonObject _getJson(QModelIndex, qint32 depth);
    quint64 _dirSize(QModelIndex);
    //quint64 _fileCount(QModelIndex);
    //quint64 _nExec(QModelIndex);
    const ExtStat* const _getExt(QModelIndex);
    const OwnStat* const _getOwn(QModelIndex);
    const GroupStat* const _getGroup(QModelIndex);
public:
    StatisticsThread(QFileSystemModel *);
    
    QJsonObject getJson(QModelIndex, qint32 depth);
    void dirSize(QModelIndex);
    quint64 fileCount(QModelIndex);
    quint64 nExec(QModelIndex);
    void getExt(QModelIndex);
    void getOwn(QModelIndex);
    void getGroup(QModelIndex);
    
    QFileInfoList* lExec();
    void lExecClear();
    bool isRunning() const;

signals:
    void dirSizeSignal(QModelIndex);
    void getExtSignal(QModelIndex);
    void getOwnSignal(QModelIndex);
    void getGroupSignal(QModelIndex);
};

#endif // DIRECTORYEXPLORERTHREAD_H
