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
#include "interactivechart.h"
#include <QJsonDocument>
#include <QPushButton>
#include "barchart.h"
#include "fileinfo.h"

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
    void onTreeItemClicked(QModelIndex index);
    void onListItemClicked (QModelIndex index);
    void upButtonPressed();
    void on_actionCheck_Disk_Fragmentation_triggered();
    void forwardButtonPressed();
    void backButtonPressed();

    void on_actionCheck_Security_Threats_triggered();

public slots:
    void dirSizeSlot(QModelIndex);
    void getExtSlot(QModelIndex);
    void getOwnSlot(QModelIndex);
    void getGroupSlot(QModelIndex);

private:
    Ui::FileExplorer *ui;
    QToolBar *mainToolBar;
    QTabWidget* ownershipTabBar;
    CheckDiskFragmentation* chkFrgmntionWin;
    CheckSecurityThreats* chckScurityThreats;
    BarChart* userOwnershipBarChart;
    BarChart* groupOwnershipBarChart;
    QLabel* selectedFileNameLabel;
    QLabel* selectedFileSizeLabel;
    QVBoxLayout* infoLayout;
    FileInfo* fileInfo;
    QStandardItemModel* permissionsModel;
    QVector<QVector<bool> > permissionsGrid;
    QTableView* permissionsTable;

    QLabel* ownershipLoadingBar;
    QLabel* infoLoadingBar;
    QLabel* extensionsLoadingBar;
    QLabel* permissionsLoadingBar;

    QMovie* spinnerMovie;

    QTabWidget* permissons_ownership_tab;


    void updateOwnsershipGroupsGraph(QModelIndex index);
    void initializeOwnershipCharts();
    void updateInfo(QModelIndex index);
    void initializePermissionsTable();
    void initializeInfoBox();
    void initializePermissionsOwnershipTab();
    void updatePermissionsTable(QModelIndex index);


    //Stats
    StatisticsThread* Stats;
    QFileSystemModel *dirModel;
    void StatsInit();
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

    //JS_shananigans
        InteractiveChart* chart;

};

#endif // FILEEXPLORER_H
