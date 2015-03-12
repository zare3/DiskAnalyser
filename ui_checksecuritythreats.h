/********************************************************************************
** Form generated from reading UI file 'checksecuritythreats.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKSECURITYTHREATS_H
#define UI_CHECKSECURITYTHREATS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_CheckSecurityThreats
{
public:
    QLabel *tempDirLabel;
    QTableView *threatsTableView;
    QLabel *securityThreatsCountLabel;
    QLabel *numExecutablesTitleLabel;

    void setupUi(QDialog *CheckSecurityThreats)
    {
        if (CheckSecurityThreats->objectName().isEmpty())
            CheckSecurityThreats->setObjectName(QStringLiteral("CheckSecurityThreats"));
        CheckSecurityThreats->resize(515, 384);
        tempDirLabel = new QLabel(CheckSecurityThreats);
        tempDirLabel->setObjectName(QStringLiteral("tempDirLabel"));
        tempDirLabel->setGeometry(QRect(177, 30, 161, 27));
        QFont font;
        font.setPointSize(17);
        tempDirLabel->setFont(font);
        threatsTableView = new QTableView(CheckSecurityThreats);
        threatsTableView->setObjectName(QStringLiteral("threatsTableView"));
        threatsTableView->setGeometry(QRect(20, 130, 471, 230));
        threatsTableView->horizontalHeader()->setStretchLastSection(true);
        securityThreatsCountLabel = new QLabel(CheckSecurityThreats);
        securityThreatsCountLabel->setObjectName(QStringLiteral("securityThreatsCountLabel"));
        securityThreatsCountLabel->setGeometry(QRect(350, 80, 70, 17));
        numExecutablesTitleLabel = new QLabel(CheckSecurityThreats);
        numExecutablesTitleLabel->setObjectName(QStringLiteral("numExecutablesTitleLabel"));
        numExecutablesTitleLabel->setGeometry(QRect(130, 80, 201, 20));
        QFont font1;
        font1.setPointSize(13);
        numExecutablesTitleLabel->setFont(font1);

        retranslateUi(CheckSecurityThreats);

        QMetaObject::connectSlotsByName(CheckSecurityThreats);
    } // setupUi

    void retranslateUi(QDialog *CheckSecurityThreats)
    {
        CheckSecurityThreats->setWindowTitle(QApplication::translate("CheckSecurityThreats", "Dialog", 0));
        tempDirLabel->setText(QApplication::translate("CheckSecurityThreats", "directory: /tmp", 0));
        securityThreatsCountLabel->setText(QApplication::translate("CheckSecurityThreats", "TextLabel", 0));
        numExecutablesTitleLabel->setText(QApplication::translate("CheckSecurityThreats", "Number of Executables:", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckSecurityThreats: public Ui_CheckSecurityThreats {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKSECURITYTHREATS_H
