#include "StatisticsThread.h"
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>

void StatisticsThread::run(){
    //qDebug() << QString("Was here!");
    dirSize(fsModel->index(fsModel->rootPath()));
    done = true;
}
StatisticsThread::StatisticsThread(QFileSystemModel *ptr){
    fsModel = ptr;
    done = false;
    QThread::start();
}

quint64 StatisticsThread::dirSize(QModelIndex idx){ //Return the sum of sizes of all the files and subfolders of the current directory
    QFileInfo fInfo = fsModel->fileInfo(idx);
    if(fInfo.isFile()) return fInfo.isFile();
    if(mpSize.contains(idx)) return mpSize[idx];
    quint64& ret = mpSize[idx];
    ret = 0;
    
    QDir dInfo = fInfo.absoluteDir();
    QFileInfoList dList = dInfo.entryInfoList(QDir::AllEntries | QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
    for(int i = 0; i < dList.size(); i++)
        ret += dirSize(fsModel->index(dList[i].absoluteFilePath())); 
    return ret;
}

bool StatisticsThread::hasExec(QModelIndex idx){    //Returns true if the directory or any of its children have an executeable file.
    QFileInfo fInfo = fsModel->fileInfo(idx);
    if(fInfo.isFile() && fInfo.isExecutable()) return true;
    if(fInfo.isFile() && !fInfo.isExecutable()) return false;
    if(mpHasExec.contains(idx)) return mpHasExec[idx];
    
    bool& ret = mpHasExec[idx]; ret = false;
    QDir dInfo = fInfo.absoluteDir();
    QFileInfoList dList = dInfo.entryInfoList(QDir::AllDirs | QDir::Drives | QDir::Hidden);
    for(int i = 0; i < dList.size(); i++)
        if(hasExec(fsModel->index(dList[i].absoluteFilePath())))
            ret = true;
    if(dInfo.entryInfoList(QDir::Files | QDir::Executable | QDir::System).size())
        ret = true;
    return ret;
}

bool StatisticsThread::isReady() const{
    return done;
}
