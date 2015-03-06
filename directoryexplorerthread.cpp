#include "directoryexplorerthread.h"
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>

void DirectoryExplorerThread::run()
{
    quint64 result = dirSize(filePath);
    emit (resultReady(result));
}

quint64 DirectoryExplorerThread::dirSize(const QString & str)
{
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
    return sizex;
}

