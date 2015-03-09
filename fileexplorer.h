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
#include "checkdiskfragmentation.h"
#include <QStack>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include "StatisticsThread.h"
#include "checksecuritythreats.h"
#include "ExtTreeModel.h"
#include "barchart.h"

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
    void onListItemClicked (QModelIndex index);
    void upButtonPressed();
    void on_actionCheck_Disk_Fragmentation_triggered();
    void forwardButtonPressed();
    void backButtonPressed();

    void on_actionCheck_Security_Threats_triggered();

private:
    Ui::FileExplorer *ui;
    QToolBar *toolBar;
    QToolBar *mainToolBar;
    CheckDiskFragmentation* chkFrgmntionWin;
    CheckSecurityThreats* chckScurityThreats;
    BarChart* ownershipBarChart;
    QLabel* selectedFileNameLabel;
    QLabel* selectedFileSizeLabel;
    QVBoxLayout* infoLayout;

    //Stats
    StatisticsThread* Stats;
    QFileSystemModel *dirModel;
    //End of Stats
    
    //DirTreeView
    QTreeView *dirTreeView;
    QListView *dirListView;
    QTabWidget *dirTabWidget;
    QStack<QString> backStack, forwardStack;
    void initializeDirectory();
    //End of DirTreeView

    //Extentions
    QTreeView *tv_ext;
    ExtTreeModel* extModel;
    void extinit();
    //End of Extentions

};

#endif // FILEEXPLORER_H
