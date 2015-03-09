#include "fileexplorer.h"
#include "ui_fileexplorer.h"
#include <QDebug>
#include <QToolButton>
#include <QGroupBox>
#include <QVBoxLayout>

FileExplorer::FileExplorer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileExplorer)
{
    ui->setupUi(this);
    QWidget::showMaximized();

    QString filePath = "/";
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(filePath);
    Stats = new StatisticsThread(dirModel);
    while(!Stats->isReady());

     userOwnershipBarChart = new BarChart(this);
     groupOwnershipBarChart = new BarChart (this);
     ownershipTabBar = new QTabWidget (this);

     infoLayout = new QVBoxLayout(this);
     selectedFileNameLabel = new QLabel(this);
     selectedFileSizeLabel = new QLabel(this);


     fileInfo = new FileInfo(dirModel);

     permissionsTable = new QTableView(this);

    initializeDirectory();
    initializeOwnershipCharts();
    extinit();
}

void FileExplorer::initializeDirectory()
{
    dirTreeView = new QTreeView(this);
    dirListView = new QListView(this);
    dirTabWidget = new QTabWidget(this);

    toolBar = new QToolBar(this);
    mainToolBar = new QToolBar (this);
    QGroupBox* groupBox = new QGroupBox(this);
    QToolButton *upButton = new QToolButton(this);
    QToolButton *backButton = new QToolButton(this);
    QToolButton *forwardButton = new QToolButton(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    toolBar->addWidget(upButton);
    toolBar->addWidget(backButton);
    toolBar->addWidget(forwardButton);



    upButton->setIcon(QIcon(":/folder/icons/up.png"));
    backButton->setIcon(QIcon(":/folder/icons/left.png"));
    forwardButton->setIcon(QIcon(":/folder/icons/right.png"));

    toolBar->setIconSize(QSize(16,16));

    dirListView->setResizeMode(QListView::Adjust);


    vbox->addWidget(toolBar);
    vbox->addWidget(dirListView);
    groupBox->setLayout(vbox);

    //groupBox->setStyleSheet("");

    dirTabWidget->addTab(dirTreeView, "");
    dirTabWidget->setTabIcon(0, QIcon(":/folder/icons/tree.png"));
    dirTabWidget->addTab(groupBox, "");
    dirTabWidget->setTabIcon(1, QIcon(":/folder/icons/grid.png"));
    dirTabWidget->setTabPosition(QTabWidget::West);
    ui->treeDockWidget->setWidget(dirTabWidget);

    vbox->setMargin(0);
    vbox->setSpacing(0);
    //vbox->setContentsMargins();

    dirTreeView->setModel(dirModel);

    dirListView->setModel(dirModel);
    dirListView->setViewMode(QListView::IconMode);
    dirListView->setSpacing(10);
    dirListView->setUniformItemSizes(true);
    dirListView->setRootIndex(dirModel->index("/"));



    connect(dirListView, SIGNAL(clicked(QModelIndex)), this, SLOT(onListItemClicked(QModelIndex)));
    connect(dirListView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(onListItemDoubleClicked(QModelIndex)));
    connect(dirTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(onTreeItemClicked(QModelIndex)));
    connect(upButton, SIGNAL(clicked ()), this, SLOT(upButtonPressed()));
    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonPressed()));
    connect(forwardButton, SIGNAL(clicked()), this, SLOT(forwardButtonPressed()));
}

FileExplorer::~FileExplorer()
{
    delete ui;
}

void FileExplorer::extinit(){
    tv_ext = new QTreeView(this);
    extModel = new ExtTreeModel(this, Stats);
    tv_ext->setModel(extModel);
    tv_ext->setAlternatingRowColors(true);
    ui->dw_ext->setWidget(tv_ext);
}

void FileExplorer::onListItemClicked(QModelIndex index)
{
    updateInfo(index);
    updateOwnershipUsersGraph(index);
    updateOwnsershipGroupsGraph(index);
    extModel->SetDir(index);
    ui->dw_ext->setWidget(tv_ext);

}

void FileExplorer::onListItemDoubleClicked(QModelIndex index)
{
    if(dirModel->fileInfo(index).isDir()){
        forwardStack.clear();
        backStack.push(dirModel->filePath(dirListView->rootIndex()));
        dirListView->setRootIndex(index);
        dirTreeView->setCurrentIndex(index);
    }
    else{
        if(dirModel->fileInfo(index).isExecutable()){
            QString program = dirModel->filePath(index);
            QStringList arguments;
            QProcess *myProcess = new QProcess(this);
            myProcess->start(program, arguments);
        }
        else{
            QDesktopServices::openUrl(QUrl::fromLocalFile(dirModel->filePath(index)));
        }
    }
}

void FileExplorer::onTreeItemClicked(QModelIndex index)
{
    if(dirModel->fileInfo(index).isDir()){
        forwardStack.clear();
        backStack.push(dirModel->filePath(dirListView->rootIndex()));
        dirListView->setRootIndex(index);
    }
}


void FileExplorer::upButtonPressed()
{
    forwardStack.clear();
    backStack.push(dirModel->filePath(dirListView->rootIndex()));
    QDir dir (dirModel->filePath(dirListView->rootIndex()));
    dir.cdUp();

    dirListView->setRootIndex(dirModel->index(dir.path()));
}

void FileExplorer::backButtonPressed()
{
    if(backStack.size() > 0){
        forwardStack.push(dirModel->filePath(dirListView->rootIndex()));
        QString nextPath = backStack.top();
        backStack.pop();
        dirListView->setRootIndex(dirModel->index(nextPath));
    }
}

void FileExplorer::forwardButtonPressed()
{
    if(forwardStack.size() > 0){
        backStack.push(dirModel->filePath(dirListView->rootIndex()));
        QString nextPath = forwardStack.top();
        forwardStack.pop();
        dirListView->setRootIndex(dirModel->index(nextPath));
    }
}

void FileExplorer::on_actionCheck_Disk_Fragmentation_triggered()
{
    chkFrgmntionWin = new CheckDiskFragmentation(this);
    (*chkFrgmntionWin).show();
}

void FileExplorer::on_actionCheck_Security_Threats_triggered()
{
    chckScurityThreats = new CheckSecurityThreats(dirModel,Stats,this);
    (*chckScurityThreats).show();
}

void FileExplorer::updateOwnershipUsersGraph(QModelIndex index){
    //fileInfo->calcOwners(dirModel->fileInfo(index).filePath());
    const StatisticsThread::OwnStat* const owners = Stats->getOwn(index);
    qDebug()<<"TEST";
    //QVector<UserOwner>* owners = fileInfo->getOwners();
    QVector<Piece>* pieces = new QVector<Piece> ();
    //for (int i=0; i<owners->size(); i++)
    for(QMap<QString, quint64>::const_iterator it = owners->nOwn.begin(); it != owners->nOwn.end(); it++){
       Piece t;
       t.color = Qt::green;
       t.name = it.key();//owners->at(i).ownerName;
       t.percentage = it.value();//owners->at(i).numOwnedFiles.toDouble();
       qDebug()<<t.name;
       pieces->push_back(t);
    }


    userOwnershipBarChart->setData(1,pieces);
    userOwnershipBarChart->update();
}

void FileExplorer::updateOwnsershipGroupsGraph(QModelIndex index){
    //fileInfo->calcGroups(dirModel->fileInfo(index).filePath());
    const StatisticsThread::GroupStat* const groups = Stats->getGroup(index);
    //QVector<GroupOwner>* groups = fileInfo->getGroups();
    QVector<Piece>* pieces = new QVector<Piece> ();
    //for (int i=0; i<groups->size(); i++)
    for(QMap<QString, quint64>::const_iterator it = groups->nGroup.begin(); it != groups->nGroup.end(); it++){
       Piece t;
       t.color = Qt::green;
       t.name = it.key();   //groups->at(i).groupName;
       t.percentage = it.value();   //groups->at(i).numOwnedFiles.toDouble();
       pieces->push_back(t);
    }


    groupOwnershipBarChart->setData(1,pieces);
    groupOwnershipBarChart->update();
}

void FileExplorer::initializeOwnershipCharts()
{
    ownershipTabBar->addTab(userOwnershipBarChart, "Users");
    ownershipTabBar->setTabIcon(0, QIcon(":/folder/icons/tree.png"));
    ownershipTabBar->addTab(groupOwnershipBarChart, "Groups");
    ownershipTabBar->setTabIcon(1, QIcon(":/folder/icons/grid.png"));
    ownershipTabBar->setTabPosition(QTabWidget::West);
    ui->ownershipChartDockWidget->setWidget(ownershipTabBar);


    ui->ownershipChartDockWidget->setMinimumSize(400,120);
}

void FileExplorer::updateInfo(QModelIndex index)
{
    QWidget* multiWidget = new QWidget();
    selectedFileNameLabel->setText(fileInfo->getName(dirModel->fileInfo(index).filePath()));
    selectedFileSizeLabel->setText(QString::number(Stats->dirSize(index)));


    infoLayout->addWidget(selectedFileNameLabel);
    infoLayout->addWidget(selectedFileSizeLabel);


    permissionsModel = new QStandardItemModel(4,3,this); //2 Rows and 3 Columns
    permissionsModel->setHorizontalHeaderItem(0, new QStandardItem(QString("READ")));
    permissionsModel->setHorizontalHeaderItem(1, new QStandardItem(QString("WRITE")));
    permissionsModel->setHorizontalHeaderItem(2, new QStandardItem(QString("EXECUTE")));
    permissionsModel->setVerticalHeaderItem(0, new QStandardItem(QString("OWNER")));
     permissionsModel->setVerticalHeaderItem(1, new QStandardItem(QString("GROUP")));
      permissionsModel->setVerticalHeaderItem(2, new QStandardItem(QString("USER")));
       permissionsModel->setVerticalHeaderItem(3, new QStandardItem(QString("OTHER")));
    permissionsGrid = fileInfo->getPermissions(dirModel->fileInfo(index).filePath());


    for (int i=0; i<4; i++)
    {
        for (int j=0; j<3; j++)
        {
           permissionsModel->setItem(i,j,new QStandardItem(QString::number(permissionsGrid.at(i).at(j))));
        }
    }

    permissionsTable->setModel(permissionsModel);
    ui->permissionsDockWidget->setWidget(permissionsTable);


    multiWidget->setLayout(infoLayout);

    ui->informationDockWidget->setWidget(multiWidget);
}
