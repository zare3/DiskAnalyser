#include "StatisticsThread.h"
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QMessageBox>

void StatisticsThread::run(){
    QModelIndex start = fsModel->index("/");
    qDebug() << fsModel->filePath(start);
    //nExec(start);
    qDebug() << "hasExec is done";
    //dirSize(start);
    qDebug() << "dirSize is done";
    getExt(start);
    qDebug() << "getExt is done";
    done = true;
    qDebug() << "Thread is done";
}
StatisticsThread::StatisticsThread(QFileSystemModel *ptr){
    fsModel = ptr;
    done = false;
    QThread::start();
}

/*quint64 StatisticsThread::dirSize(const QString & str)
{
    quint64 sizex = 0;
    QFileInfo str_info(str);
    if (str_info.isDir())
    {
        QDir dir(str);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Hidden); // QDir::Hidden | QDir::NoSymLinks |
        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            if(fileInfo.isDir())
            {
                sizex += dirSize(fileInfo.absoluteFilePath());
            }
            else
                sizex += fileInfo.size();

        }
    }
    qDebug() << str;
    return mpSize[fsModel->index(str)] = sizex;
}*/
quint64 StatisticsThread::dirSize(QModelIndex idx){
    //Return the sum of sizes of all the files and subfolders of the current directory
    QFileInfo fInfo = fsModel->fileInfo(idx);
    
    if(fInfo.isFile()) return fInfo.size();
    //qDebug() << fInfo.absoluteFilePath();
    //qDebug() << idx;
    if(mpSize.contains(idx)) return mpSize[idx];
    quint64& ret = mpSize[idx];
    ret = 0;
    
    QDir dInfo (fInfo.absoluteFilePath());
    QFileInfoList dList = dInfo.entryInfoList(QDir::Files | QDir::Dirs |  QDir::NoDotAndDotDot | QDir::NoSymLinks) ;//| QDir::Hidden | QDir::System);
    
    //qDebug() << dList[0].absoluteFilePath();
    for(int i = 0; i < dList.size(); i++)
        ret += dirSize(fsModel->index(dList[i].absoluteFilePath())); 
    
    //qDebug() << fInfo.absoluteFilePath();
    return ret;
}

quint64 StatisticsThread::nExec(QModelIndex idx){
    //Returns number of Executable files in a given directory.
    QFileInfo fInfo = fsModel->fileInfo(idx);
    if(fInfo.isFile() && fInfo.isExecutable()) {
        fiLExec.append(fInfo);
        return 1;
    }
    if(fInfo.isFile() && !fInfo.isExecutable()) return 0;
    if(mpNExec.contains(idx)) return mpNExec[idx];
    
    quint64& ret = mpNExec[idx]; ret = 0;
    QDir dInfo(fInfo.absoluteFilePath());
    QFileInfoList dList = dInfo.entryInfoList(QDir::Files | QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    for(int i = 0; i < dList.size(); i++)
        ret += nExec(fsModel->index(dList[i].absoluteFilePath()));
    // qDebug() << fInfo.absoluteFilePath();
    return ret;
}
QFileInfoList *StatisticsThread::lExec(){
    return &fiLExec;
}
void StatisticsThread::lExecClear(){
    fiLExec.clear();
}

const StatisticsThread::ExtStat* const StatisticsThread::getExt(QModelIndex idx){
    //Returns statistics about the files inside a given directory.
    QFileInfo fInfo = fsModel->fileInfo(idx);
    if(fInfo.isFile()) return 0;
    if(mpExt.contains(idx)) return &mpExt[idx];
    
    ExtStat& ret = mpExt[idx];
    
    QDir dInfo (fInfo.absoluteFilePath());
    QFileInfoList fList = dInfo.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for(int i = 0; i < fList.size(); i++) ret.nExt[fList[i].completeSuffix()]++;
    QFileInfoList dList = dInfo.entryInfoList(QDir::Dirs | QDir::Hidden | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    for(int i = 0; i < dList.size(); i++){
        getExt(fsModel->index(dList[i].absoluteFilePath()));
        ExtStat& r = mpExt[fsModel->index(dList[i].absoluteFilePath())];
        for(QMap<QString, quint64>::iterator it = r.nExt.begin(); it != r.nExt.end(); it++)
            ret.nExt[it.key()] += it.value();
    }
    qDebug() << fInfo.absoluteFilePath();
    return &mpExt[idx];
}

bool StatisticsThread::isReady() const{
    return done;
}
