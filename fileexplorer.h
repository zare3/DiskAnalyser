#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>
#include <QTabWidget>
#include <QToolBar>
#include <QStack>
#include "directoryexplorerthread.h"
namespace Ui {
class FileExplorer;
}

class FileExplorer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileExplorer(QWidget *parent = 0);
    ~FileExplorer();

private slots:
    void onListItemDoubleClicked(QModelIndex index);
    void upButtonPressed();
    void forwardButtonPressed();
    void backButtonPressed();

    void resultsFinished(quint64);
private:
    Ui::FileExplorer *ui;
    QFileSystemModel *dirModel;
    QTreeView *dirTreeView;
    QListView *dirListView;
    QTabWidget *dirTabWidget;
    QToolBar *toolBar;
    DirectoryExplorerThread* directoryThread;

    QStack<QString> backStack, forwardStack;

    void initializeDirectory();
};

#endif // FILEEXPLORER_H
