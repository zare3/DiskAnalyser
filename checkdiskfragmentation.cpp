#include "checkdiskfragmentation.h"
#include "ui_checkdiskfragmentation.h"

CheckDiskFragmentation::CheckDiskFragmentation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDiskFragmentation)
{
    ui->setupUi(this);
    setWindowTitle("Check Disk Fragmentation");
    index = -1;

    QStringList getPrtnsArgs;
    getPrtnsArgs<<"-l";
    QString getAllPrtitions = executeTerminalCmnd("fdisk",getPrtnsArgs);
    qDebug()<<getAllPrtitions;

    QRegExp rx ("/dev/sd\\w+\\d");
    QStringList prtitionsStringList;
    int pos = 0;
    while ((pos=rx.indexIn(getAllPrtitions,pos))!=-1){
        prtitionsStringList.append(rx.cap());
        pos+=rx.matchedLength();
    }

    for (int i=0; i<prtitionsStringList.size(); i++)
    {
        // qDebug() <<  "DRIVES" << prtitionsStringList.at(i) <<"/n";
        ui->prtitionsCmboBx->addItem(prtitionsStringList.at(i));
    }


}


QString CheckDiskFragmentation:: executeTerminalCmnd(QString cmnd, QStringList args)
{
    QProcess OProcess;

    //cmnd = "fdisk";
    // args<<"-l"<<"/";

    OProcess.start(cmnd,args,QIODevice::ReadOnly); //Starts execution of command
    OProcess.waitForFinished(); //Waits for execution to complete

    QString out = OProcess.readAllStandardOutput(); //Reads standard output
    QString err = OProcess.readAllStandardError(); //Reads standard error

    qDebug()<<"\n Printing the standard output..........\n";
    qDebug()<<out;
    qDebug()<<"\n Printing the standard error..........\n";
    qDebug()<<err;

    return out;
}

CheckDiskFragmentation::~CheckDiskFragmentation()
{
    delete ui;
}

void CheckDiskFragmentation::on_prtitionsCmboBx_currentIndexChanged(const QString &arg1)
{
    QStringList getFragmntationArgs;
    getFragmntationArgs<<"-fn"<<arg1;
    QString contigousPercentage = executeTerminalCmnd("fsck",getFragmntationArgs);

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

        ui->pieChart->setIndex(index);
        ui->pieChart->update();
    }

}
