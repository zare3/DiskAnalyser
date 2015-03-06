#ifndef DIRECTORYEXPLORERTHREAD_H
#define DIRECTORYEXPLORERTHREAD_H
#include <QThread>

class DirectoryExplorerThread : public QThread
{
    Q_OBJECT
      void run();
private:
    quint64 dirSize(const QString &str);
public:
    QString filePath;



signals:
    void resultReady(quint64 x);
};

#endif // DIRECTORYEXPLORERTHREAD_H
