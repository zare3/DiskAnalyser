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
    
    ui->chart_widget->setMinimumSize(400,300);
    
    spinnerMovie = new QMovie(":/folder/icons/loading.gif");
    
    ownershipLoadingBar = new QLabel();
    ownershipLoadingBar->setMovie(spinnerMovie);
    permissionsLoadingBar = new QLabel();
    permissionsLoadingBar->setMovie(spinnerMovie);
    infoLoadingBar = new QLabel();
    infoLoadingBar->setMovie(spinnerMovie);
    extensionsLoadingBar = new QLabel();
    extensionsLoadingBar->setMovie(spinnerMovie);

    spinnerMovie->start();

    initializeInfoBox();
    initializeDirectory();
    initializePermissionsTable();
    initializeOwnershipCharts();
    initializePermissionsOwnershipTab();
    extinit();
    initializeView();
   // updateWholeView(dirModel->index("/"));




    connect(Stats, SIGNAL(dirSizeSignal(QModelIndex)), this, SLOT(dirSizeSlot(QModelIndex)));
    connect(Stats, SIGNAL(getExtSignal(QModelIndex)), this, SLOT(getExtSlot(QModelIndex)));
    connect(Stats, SIGNAL(getOwnSignal(QModelIndex)), this, SLOT(getOwnSlot(QModelIndex)));
    connect(Stats, SIGNAL(getGroupSignal(QModelIndex)), this, SLOT(getGroupSlot(QModelIndex)));





}

void FileExplorer::initializeDirectory()
{
    dirTreeView = new QTreeView(this);
    dirListView = new QListView(this);
    dirTabWidget = new QTabWidget(this);
    chart = new InteractiveChart(this);

    mainToolBar = new QToolBar (this);
    QWidget* groupBox = new QWidget(this);
    QToolButton *upButton = new QToolButton(this);
    QToolButton *backButton = new QToolButton(this);
    QToolButton *forwardButton = new QToolButton(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    //QHBoxLayout *hbox = new QHBoxLayout(this);
    QToolBar * hbox = new QToolBar(this);
    hbox->addWidget(upButton);
    hbox->addWidget(backButton);
    hbox->addWidget(forwardButton);


    QPixmap temppixmap(":/folder/icons/up_btn.png");
    QIcon buttonIcon= QIcon(temppixmap);
    upButton->setIcon(buttonIcon);
    upButton->setIconSize(QSize(30, 30));
    upButton->setFixedSize(QSize(30, 30));

    temppixmap = QPixmap(":/folder/icons/back_btn.png");
    buttonIcon= QIcon(temppixmap);
    backButton->setIcon(buttonIcon);
    backButton->setIconSize(QSize(30, 30));
    backButton->setFixedSize(QSize(30, 30));

    temppixmap= QPixmap(":/folder/icons/forward_btn.png");
    buttonIcon= QIcon(temppixmap);
    forwardButton->setIcon(buttonIcon);
    forwardButton->setIconSize(QSize(30, 30)); //(temppixmap.rect().size());
    forwardButton->setFixedSize(QSize(30, 30));

    /*
    QPixmap pixmap;
    //pixmap.load(":/folder/icons/up_btn.png");
    //upButton->setMask(pixmap.createMaskFromColor(Qt::transparent,Qt::MaskOutColor));
    pixmap.load(":/folder/icons/circle_btn_mask.png");

    backButton->setMask(pixmap.createMaskFromColor(Qt::transparent,Qt::MaskInColor).scaled(QSize(30, 30)));
    forwardButton->setMask(pixmap.createMaskFromColor(Qt::transparent,Qt::MaskInColor).scaled(QSize(30, 30)));

    pixmap.load(":/folder/icons/up_btn.png");
    upButton->setMask(pixmap.createMaskFromColor(Qt::transparent,Qt::MaskInColor).scaled(upButton->size()));
    */

    dirListView->setResizeMode(QListView::Adjust);


    vbox->addWidget(hbox);
    vbox->addWidget(dirListView);
    groupBox->setLayout(vbox);

    //groupBox->setStyleSheet("");

    dirTabWidget->addTab(dirTreeView, "");
    dirTabWidget->setTabIcon(0, QIcon(QPixmap(":/folder/icons/tree.png").scaledToHeight(30)));
    dirTabWidget->addTab(groupBox, "");
    dirTabWidget->setTabIcon(1, QIcon(QPixmap(":/folder/icons/grid.png").scaledToHeight(30)));
    dirTabWidget->setTabPosition(QTabWidget::West);
    ui->treeDockWidget->setWidget(dirTabWidget);
    ui->chart_widget->setWidget(chart->GetChart());

    vbox->setMargin(0);
    vbox->setSpacing(0);
    //vbox->setContentsMargins();

    dirTreeView->setModel(dirModel);

    dirListView->setModel(dirModel);
    dirListView->setViewMode(QListView::IconMode);
    dirListView->setSpacing(10);
    dirListView->setUniformItemSizes(true);
    dirListView->setRootIndex(dirModel->index("/"));
    QFile jsonfile("TEMP_FILE.json");
    jsonfile.open(QFile::WriteOnly);
    jsonfile.write(QJsonDocument(Stats->getJson(dirModel->index("/home"),qint32(0))).toJson(QJsonDocument::Indented));//.toJson(QJsonDocument::Compact);

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
    tv_ext->header()->close();
    ui->dw_ext->setWidget(tv_ext);
}

void FileExplorer::onListItemClicked(QModelIndex index)
{
    updateWholeView(index);

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

    updateWholeView(index);

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

void FileExplorer::initializeOwnershipCharts()
{
    userOwnershipBarChart = new BarChart(this);
    groupOwnershipBarChart = new BarChart (this);
    ownershipTabBar = new QTabWidget (this);
    ownershipTabBar->addTab(userOwnershipBarChart, "");
    ownershipTabBar->setTabIcon(0, QIcon(QPixmap(":/folder/icons/owner.png").scaledToHeight(30)));
    //ownershipTabBar->setTabIcon(0, QIcon(":/folder/icons/owner.png"));
    ownershipTabBar->addTab(groupOwnershipBarChart, "");
    ownershipTabBar->setTabIcon(1, QIcon(QPixmap(":/folder/icons/group.png").scaledToHeight(30)));
    //ownershipTabBar->setTabIcon(1, QIcon(":/folder/icons/group.png"));
    ownershipTabBar->setTabPosition(QTabWidget::West);
}
void FileExplorer::initializePermissionsTable()
{
    permissionsTable = new QTableView(this);
    permissionsModel = new QStandardItemModel(4,3,this); //2 Rows and 3 Columns
    permissionsModel->setHorizontalHeaderItem(0, new QStandardItem(QString("READ")));
    permissionsModel->setHorizontalHeaderItem(1, new QStandardItem(QString("WRITE")));
    permissionsModel->setHorizontalHeaderItem(2, new QStandardItem(QString("EXECUTE")));
    permissionsModel->setVerticalHeaderItem(0, new QStandardItem(QString("OWNER")));
    permissionsModel->setVerticalHeaderItem(1, new QStandardItem(QString("GROUP")));
    permissionsModel->setVerticalHeaderItem(2, new QStandardItem(QString("USER")));
    permissionsModel->setVerticalHeaderItem(3, new QStandardItem(QString("OTHER")));
}
void FileExplorer::initializeInfoBox()
{
    infoLayout = new QVBoxLayout(this);
    selectedFileNameLabel = new QLabel(this);
    selectedFileSizeLabel = new QLabel(this);
    fileInfo = new FileInfo(dirModel);
}

void FileExplorer::initializePermissionsOwnershipTab()
{
    permissons_ownership_tab = new QTabWidget(this);
    permissons_ownership_tab->addTab(ownershipTabBar,"Tab 1");
    permissons_ownership_tab->addTab(permissionsTable,"Tab 2");
    ownershipTabBar->setTabPosition(QTabWidget::South);
    ui->ownershipChartDockWidget->setWidget(permissons_ownership_tab);
}
void FileExplorer::updatePermissionsTable(QModelIndex index)
{
    permissionsGrid = fileInfo->getPermissions(dirModel->fileInfo(index).filePath());
    for (int i=0; i<4; i++)
        for (int j=0; j<3; j++)
           permissionsModel->setItem(i,j,new QStandardItem(QString::number(permissionsGrid.at(i).at(j))));
    permissionsTable->setModel(permissionsModel);
    ui->ownershipChartDockWidget->setWidget(permissons_ownership_tab);
}

void FileExplorer::initializeView()
{
    ui->ownershipChartDockWidget->setMaximumHeight(380);
    ui->informationDockWidget->setMinimumWidth(200);

    ui->chart_widget->setVisible(true);
    ui->treeDockWidget->setVisible(true);
    ui->informationDockWidget->setVisible(true);
    ui->ownershipChartDockWidget->setVisible(true);
    ui->dw_ext->setVisible(true);
    ui->permissionsDockWidget->setVisible(true);

    removeDockWidget(ui->chart_widget);
    removeDockWidget(ui->treeDockWidget);
    removeDockWidget(ui->informationDockWidget);
    removeDockWidget(ui->ownershipChartDockWidget);
    removeDockWidget(ui->dw_ext);
    removeDockWidget(ui->permissionsDockWidget);

    addDockWidget(Qt::LeftDockWidgetArea,ui->chart_widget);
    setCentralWidget(ui->chart_widget);
    addDockWidget(Qt::LeftDockWidgetArea,ui->treeDockWidget);

    addDockWidget(Qt::RightDockWidgetArea,ui->informationDockWidget);

    addDockWidget(Qt::BottomDockWidgetArea,ui->ownershipChartDockWidget);
    addDockWidget(Qt::BottomDockWidgetArea,ui->dw_ext);

    ui->chart_widget->setFloating(false);
    ui->treeDockWidget->setFloating(false);
    ui->informationDockWidget->setFloating(false);
    ui->ownershipChartDockWidget->setFloating(false);
    ui->dw_ext->setFloating(false);
    ui->permissionsDockWidget->setFloating(false);

    ui->chart_widget->setVisible(true);
    ui->treeDockWidget->setVisible(true);
    ui->informationDockWidget->setVisible(true);
    ui->ownershipChartDockWidget->setVisible(true);
    ui->dw_ext->setVisible(true);
    ui->permissionsDockWidget->setVisible(true);
}

void FileExplorer::updateWholeView(QModelIndex index)
{
    updatePermissionsTable(index);
    ui->informationDockWidget->setWidget(infoLoadingBar);
    Stats->dirSize(index);
    ui->ownershipChartDockWidget->setWidget(ownershipLoadingBar);
    Stats->getOwn(index);
    ui->ownershipChartDockWidget->setWidget(ownershipLoadingBar);
    Stats->getGroup(index);
    ui->dw_ext->setWidget(extensionsLoadingBar);
    Stats->getExt(index);
}

void FileExplorer::dirSizeSlot(QModelIndex idx){
    QWidget* multiWidget = new QWidget();
    selectedFileNameLabel->setText(fileInfo->getName(dirModel->fileInfo(idx).filePath()));
    selectedFileSizeLabel->setText(QString::number(Stats->_dirSize(idx)));
    infoLayout->addWidget(selectedFileNameLabel);
    infoLayout->addWidget(selectedFileSizeLabel);
    multiWidget->setLayout(infoLayout);
    ui->informationDockWidget->setWidget(multiWidget);
}
void FileExplorer::getExtSlot(QModelIndex idx){
    extModel->SetDir(idx);
    ui->dw_ext->setWidget(tv_ext);
}
void FileExplorer::getOwnSlot(QModelIndex idx){
    const StatisticsThread::OwnStat* const owners = Stats->_getOwn(idx);
    QVector<Piece>* pieces = new QVector<Piece> ();
    for(QMap<QString, quint64>::const_iterator it = owners->nOwn.begin(); it != owners->nOwn.end(); it++){
       Piece t;
       t.color = Qt::green;
       t.name = it.key();
       t.percentage = it.value();
       qDebug()<<t.name;
       pieces->push_back(t);
    }

   ui->ownershipChartDockWidget->setWidget(permissons_ownership_tab);

    userOwnershipBarChart->setData(1,pieces);
    userOwnershipBarChart->update();
   permissons_ownership_tab->update();
}
void FileExplorer::getGroupSlot(QModelIndex idx){
    ui->ownershipChartDockWidget->setWidget(ownershipLoadingBar);
    const StatisticsThread::GroupStat* const groups = Stats->_getGroup(idx);
    QVector<Piece>* pieces = new QVector<Piece> ();
    for(QMap<QString, quint64>::const_iterator it = groups->nGroup.begin(); it != groups->nGroup.end(); it++){
       Piece t;
       t.color = Qt::green;
       t.name = it.key();
       t.percentage = it.value();
       pieces->push_back(t);
    }

   ui->ownershipChartDockWidget->setWidget(permissons_ownership_tab);

    groupOwnershipBarChart->setData(1,pieces);
    groupOwnershipBarChart->update();
    permissons_ownership_tab->update();
}
