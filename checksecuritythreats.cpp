#include "checksecuritythreats.h"
#include "ui_checksecuritythreats.h"

CheckSecurityThreats::CheckSecurityThreats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckSecurityThreats)
{
    ui->setupUi(this);

    model = new QStandardItemModel(0,2,this); //2 Rows and 3 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Path")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Issue")));

    ui->threatsTableView->setModel(model);
}

CheckSecurityThreats::~CheckSecurityThreats()
{
    delete ui;
}
