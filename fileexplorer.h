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
    void resultsFinished(quint64);
private:
    Ui::FileExplorer *ui;
    QFileSystemModel *dirModel;
    QTreeView *treeView;
    QListView *listView;
    QTabWidget *tabWidget;
    QToolBar *toolBar;
    DirectoryExplorerThread* directoryThread;
};

#endif // FILEEXPLORER_H
