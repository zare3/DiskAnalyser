#include "StatisticsThread.h"
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>

void StatisticsThread::run(){
    //dirSize(filePath);
    done = true;
}
StatisticsThread::StatisticsThread(QFileSystemModel *ptr){
    fsModel = ptr;
    done = false;
    QThread::start();
}

quint64 StatisticsThread::dirSize(QModelIndex idx){
    /*QFileInfo fInfo = fsModel->fileInfo(index);
    if(fInfo.isFile()) return fInfo.isFile();
    if(mpSize.contains(idx)) return mp[idx];
    
    quint64 sizex = 0;
    QFileInfo str_info(str);
    if (str_info.isDir())
    {
        QDir dir(str);
        QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::Dirs |  QDir::NoDotAndDotDot); // QDir::Hidden | QDir::NoSymLinks |
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
    return sizex;*/
    return 0;
}

bool StatisticsThread::hasExec(QModelIndex idx){
    QFileInfo fInfo = fsModel->fileInfo(idx);
    if(fInfo.isFile() && fInfo.isExecutable())
        return true;
    if(fInfo.isFile() && !fInfo.isExecutable()) 
        return false;
    if(mpHasExec.contains(idx))
        return mpHasExec[idx];
    bool& ret = mpHasExec[idx];
    ret = false;
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
