#include "StatisticsThread.h"
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>
#include <QMessageBox>

void StatisticsThread::run(){
    QModelIndex start = fsModel->index("/");
    qDebug() << fsModel->filePath(start);
    nExec(start);
    qDebug() << "hasExec is done";
    dirSize(start);
    done = true;
    qDebug() << "Thread was done";
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
    
    if(fInfo.isFile()) return fInfo.isFile();
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
    //Returns true if the directory or any of its children have an executeable file.
    QFileInfo fInfo = fsModel->fileInfo(idx);
    if(fInfo.isFile() && fInfo.isExecutable()) {
        fiLExec.append(fInfo);
        return 1;
    }
    if(fInfo.isFile() && !fInfo.isExecutable()) return 0;
    if(mpNExec.contains(idx)) return mpNExec[idx];
    
    quint64& ret = mpNExec[idx]; ret = 0;
    QDir dInfo(fInfo.absoluteFilePath());
    QFileInfoList dList = dInfo.entryInfoList(QDir::Files | QDir::AllDirs | QDir::Drives | QDir::Hidden | QDir::NoSymLinks);
    for(int i = 0; i < dList.size(); i++)
        ret += nExec(fsModel->index(dList[i].absoluteFilePath()));
    //ret += dInfo.entryInfoList(QDir::Files | QDir::Executable | QDir::System | QDir::NoSymLinks).size();
    //qDebug() << fInfo.absoluteFilePath();
    return ret;
}

QFileInfoList *StatisticsThread::lExec(){
    return &fiLExec;
}
void StatisticsThread::lExecClear(){
    fiLExec.clear();
}

bool StatisticsThread::isReady() const{
    return done;
}
