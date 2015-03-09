#include "checksecuritythreats.h"
#include "ui_checksecuritythreats.h"


CheckSecurityThreats::CheckSecurityThreats(QFileSystemModel* Sysmodel, StatisticsThread* ststicsThread, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckSecurityThreats)
{
    ui->setupUi(this);
    setWindowTitle("Check Security Threats");


    this->ststicsThread = ststicsThread;
    this->Sysmodel = Sysmodel;



    this->nExecutables = this->ststicsThread->nExec(Sysmodel->index("/tmp"));
    this->execList = this->ststicsThread->lExec();


    ui->securityThreatsCountLabel->setText(QString::number(this->nExecutables));



    model = new QStandardItemModel(0,2,this); //2 Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Path")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Issue")));


    qDebug()<<"IN SEC THREATS: " << this->execList->size();
    for (int i=0; i<this->execList->size(); i++)
    {

        model->setItem(i,0,new QStandardItem(QString(this->execList->at(i).filePath())));
        if (this->execList->at(i).isHidden())
        model->setItem(i,1,new QStandardItem(QString("Dangerous: Executable && Hidden Nature")));
        else model->setItem(i,1,new QStandardItem(QString("Executable Nature")));
    }

    ui->threatsTableView->setModel(model);
}

CheckSecurityThreats::~CheckSecurityThreats()
{
    delete ui;
}
