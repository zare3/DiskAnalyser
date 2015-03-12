/********************************************************************************
** Form generated from reading UI file 'checkdiskfragmentation.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKDISKFRAGMENTATION_H
#define UI_CHECKDISKFRAGMENTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include "piechart.h"

QT_BEGIN_NAMESPACE

class Ui_CheckDiskFragmentation
{
public:
    QComboBox *prtitionsCmboBx;
    QLabel *blocksLabelTitle;
    QLabel *contiguityLabelTitle;
    QLabel *filesLabelTitle;
    QLabel *fileNumbers;
    QLabel *blocksNumber;
    QLabel *contiguityPercentage;
    PieChart *pieChart;
    QLabel *sadFaceLabelImg;
    QLabel *loadingLbl;
    QLabel *unsupportedLabel;

    void setupUi(QDialog *CheckDiskFragmentation)
    {
        if (CheckDiskFragmentation->objectName().isEmpty())
            CheckDiskFragmentation->setObjectName(QStringLiteral("CheckDiskFragmentation"));
        CheckDiskFragmentation->resize(701, 491);
        prtitionsCmboBx = new QComboBox(CheckDiskFragmentation);
        prtitionsCmboBx->setObjectName(QStringLiteral("prtitionsCmboBx"));
        prtitionsCmboBx->setGeometry(QRect(190, 30, 300, 27));
        blocksLabelTitle = new QLabel(CheckDiskFragmentation);
        blocksLabelTitle->setObjectName(QStringLiteral("blocksLabelTitle"));
        blocksLabelTitle->setGeometry(QRect(200, 100, 100, 21));
        QFont font;
        font.setPointSize(14);
        blocksLabelTitle->setFont(font);
        contiguityLabelTitle = new QLabel(CheckDiskFragmentation);
        contiguityLabelTitle->setObjectName(QStringLiteral("contiguityLabelTitle"));
        contiguityLabelTitle->setGeometry(QRect(200, 130, 141, 21));
        contiguityLabelTitle->setFont(font);
        filesLabelTitle = new QLabel(CheckDiskFragmentation);
        filesLabelTitle->setObjectName(QStringLiteral("filesLabelTitle"));
        filesLabelTitle->setGeometry(QRect(200, 70, 100, 21));
        filesLabelTitle->setFont(font);
        fileNumbers = new QLabel(CheckDiskFragmentation);
        fileNumbers->setObjectName(QStringLiteral("fileNumbers"));
        fileNumbers->setGeometry(QRect(390, 70, 171, 21));
        QFont font1;
        font1.setPointSize(11);
        fileNumbers->setFont(font1);
        blocksNumber = new QLabel(CheckDiskFragmentation);
        blocksNumber->setObjectName(QStringLiteral("blocksNumber"));
        blocksNumber->setGeometry(QRect(390, 100, 181, 21));
        blocksNumber->setFont(font1);
        contiguityPercentage = new QLabel(CheckDiskFragmentation);
        contiguityPercentage->setObjectName(QStringLiteral("contiguityPercentage"));
        contiguityPercentage->setGeometry(QRect(390, 130, 171, 21));
        contiguityPercentage->setFont(font1);
        pieChart = new PieChart(CheckDiskFragmentation);
        pieChart->setObjectName(QStringLiteral("pieChart"));
        pieChart->setGeometry(QRect(10, 170, 681, 421));
        sadFaceLabelImg = new QLabel(pieChart);
        sadFaceLabelImg->setObjectName(QStringLiteral("sadFaceLabelImg"));
        sadFaceLabelImg->setGeometry(QRect(180, 0, 321, 291));
        loadingLbl = new QLabel(pieChart);
        loadingLbl->setObjectName(QStringLiteral("loadingLbl"));
        loadingLbl->setGeometry(QRect(260, -30, 181, 61));
        unsupportedLabel = new QLabel(CheckDiskFragmentation);
        unsupportedLabel->setObjectName(QStringLiteral("unsupportedLabel"));
        unsupportedLabel->setGeometry(QRect(140, 80, 531, 51));
        QFont font2;
        font2.setPointSize(20);
        unsupportedLabel->setFont(font2);

        retranslateUi(CheckDiskFragmentation);

        QMetaObject::connectSlotsByName(CheckDiskFragmentation);
    } // setupUi

    void retranslateUi(QDialog *CheckDiskFragmentation)
    {
        CheckDiskFragmentation->setWindowTitle(QApplication::translate("CheckDiskFragmentation", "Dialog", 0));
        blocksLabelTitle->setText(QApplication::translate("CheckDiskFragmentation", "#Blocks", 0));
        contiguityLabelTitle->setText(QApplication::translate("CheckDiskFragmentation", "Non Contiguity", 0));
        filesLabelTitle->setText(QApplication::translate("CheckDiskFragmentation", "#Files", 0));
        fileNumbers->setText(QApplication::translate("CheckDiskFragmentation", "12213/2313", 0));
        blocksNumber->setText(QApplication::translate("CheckDiskFragmentation", "1231231/12312", 0));
        contiguityPercentage->setText(QApplication::translate("CheckDiskFragmentation", "0.2%", 0));
        sadFaceLabelImg->setText(QString());
        loadingLbl->setText(QString());
        unsupportedLabel->setText(QApplication::translate("CheckDiskFragmentation", "Unsuppored File System Format", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckDiskFragmentation: public Ui_CheckDiskFragmentation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKDISKFRAGMENTATION_H
