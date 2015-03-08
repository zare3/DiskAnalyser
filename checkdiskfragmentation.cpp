#include "checkdiskfragmentation.h"
#include "ui_checkdiskfragmentation.h"

CheckDiskFragmentation::CheckDiskFragmentation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDiskFragmentation)
{
    ui->setupUi(this);
    setWindowTitle("Check Disk Fragmentation");
    ui->sadFaceLabelImg->setPixmap(QPixmap(":/folder/icons/sadFace.png"));
    spinnerMovie = new QMovie(":/folder/icons/loading.gif");
    ui->loadingLbl->setMovie(spinnerMovie);
    spinnerMovie->start();

    hideAll();

    index = -1;
    QStringList getPrtnsArgs;
    getPrtnsArgs<<"-l";
    getPrtitionsThread = new ExecuteTerminalCmndThread("fdisk",getPrtnsArgs);
    connect (getPrtitionsThread,SIGNAL(cmndFinished(QString)),this,SLOT(getDrivesCmndFinished(QString)));
    hideAll();
    showLoading();
    getPrtitionsThread->start();
}


void CheckDiskFragmentation::getDrivesCmndFinished(QString getAllPrtitions)
{
    QRegExp rx ("/dev/sd\\w+\\d");
    QStringList prtitionsStringList;
    int pos = 0;
    while ((pos=rx.indexIn(getAllPrtitions,pos))!=-1){
        prtitionsStringList.append(rx.cap());
        pos+=rx.matchedLength();
    }

    for (int i=0; i<prtitionsStringList.size(); i++)
    {
        ui->prtitionsCmboBx->addItem(prtitionsStringList.at(i));
    }

    hideLoading();
}

void CheckDiskFragmentation::hideAll()
{
    ui->unsupportedLabel->hide();
    ui->sadFaceLabelImg->hide();
    ui->fileNumbers->hide(); ui->filesLabelTitle->hide();
    ui->blocksLabelTitle->hide(); ui->blocksNumber->hide();
    ui->contiguityLabelTitle->hide(); ui->contiguityPercentage->hide();
    index = -1;

    ui->pieChart->setIndex(index);
    ui->pieChart->update();
}

void CheckDiskFragmentation::showLoading()
{
    ui->loadingLbl->show();
    spinnerMovie->start();
}

void CheckDiskFragmentation::hideLoading()
{
    ui->loadingLbl->hide();
}

CheckDiskFragmentation::~CheckDiskFragmentation()
{
    delete ui;
}

void CheckDiskFragmentation::on_prtitionsCmboBx_currentIndexChanged(const QString &arg1)
{
    QStringList args;
    this->arg1 = arg1;
    args<<"-fn"<<arg1;
    chkFrgmnThread = new ExecuteTerminalCmndThread("fsck", args);
    connect (chkFrgmnThread,SIGNAL(cmndFinished(QString)),this,SLOT(fragmentationCmndFinished(QString)));
    hideAll();
    showLoading();
    chkFrgmnThread->start();
}


void CheckDiskFragmentation::fragmentationCmndFinished(QString contigousPercentage )
{

    QRegExp rx = QRegExp(arg1 + ": (\\d+)/(\\d+) files \\((\\d+\\.\\d+)% non-contiguous\\), (\\d+)/(\\d+) blocks");
    index = rx.indexIn(contigousPercentage);
    QString whole;
    QString files_1;
    QString files_2;
    QString percent;
    QString blocks_1;
    QString blocks_2;
    if(index == -1) {  ui->fileNumbers->hide(); ui->filesLabelTitle->hide();
        ui->blocksLabelTitle->hide(); ui->blocksNumber->hide();
        ui->contiguityLabelTitle->hide(); ui->contiguityPercentage->hide();

        ui->unsupportedLabel->show();
        ui->sadFaceLabelImg->show();


        ui->pieChart->setIndex(index);
        ui->pieChart->update();
    }
    else{
        whole = rx.cap(0);
        files_1 = rx.cap(1);
        files_2 = rx.cap(2);
        percent = rx.cap(3);
        blocks_1 = rx.cap(4);
        blocks_2 = rx.cap(5);
        ui->fileNumbers->setText(files_1+"/"+files_2);
        ui->blocksNumber->setText(blocks_1+"/"+blocks_2);
        ui->contiguityPercentage->setText(percent+"%");
        ui->fileNumbers->show(); ui->filesLabelTitle->show();
        ui->blocksLabelTitle->show(); ui->blocksNumber->show();
        ui->contiguityLabelTitle->show(); ui->contiguityPercentage->show();

        ui->unsupportedLabel->hide();
        ui->sadFaceLabelImg->hide();


        ui->pieChart->setIndex(index);
        ui->pieChart->update();
    }
    hideLoading();
}

