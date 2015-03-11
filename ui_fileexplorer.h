/********************************************************************************
** Form generated from reading UI file 'fileexplorer.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEEXPLORER_H
#define UI_FILEEXPLORER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileExplorer
{
public:
    QAction *actionCheck_Disk_Fragmentation;
    QAction *actionCheck_Security_Threats;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuAdvanced;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *treeDockWidget;
    QWidget *dockWidgetContents;
    QDockWidget *dw_ext;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout;
    QDockWidget *ownershipChartDockWidget;
    QWidget *dockWidgetContents_3;
    QDockWidget *informationDockWidget;
    QWidget *dockWidgetContents_4;
    QDockWidget *permissionsDockWidget;
    QWidget *dockWidgetContents_5;
    QDockWidget *chart_widget;
    QWidget *dockWidgetContents_6;

    void setupUi(QMainWindow *FileExplorer)
    {
        if (FileExplorer->objectName().isEmpty())
            FileExplorer->setObjectName(QStringLiteral("FileExplorer"));
        FileExplorer->resize(671, 435);
        actionCheck_Disk_Fragmentation = new QAction(FileExplorer);
        actionCheck_Disk_Fragmentation->setObjectName(QStringLiteral("actionCheck_Disk_Fragmentation"));
        actionCheck_Security_Threats = new QAction(FileExplorer);
        actionCheck_Security_Threats->setObjectName(QStringLiteral("actionCheck_Security_Threats"));
        centralWidget = new QWidget(FileExplorer);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        FileExplorer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FileExplorer);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 671, 25));
        menuAdvanced = new QMenu(menuBar);
        menuAdvanced->setObjectName(QStringLiteral("menuAdvanced"));
        FileExplorer->setMenuBar(menuBar);
        mainToolBar = new QToolBar(FileExplorer);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        FileExplorer->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(FileExplorer);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        FileExplorer->setStatusBar(statusBar);
        treeDockWidget = new QDockWidget(FileExplorer);
        treeDockWidget->setObjectName(QStringLiteral("treeDockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        treeDockWidget->setWidget(dockWidgetContents);
        FileExplorer->addDockWidget(static_cast<Qt::DockWidgetArea>(4), treeDockWidget);
        dw_ext = new QDockWidget(FileExplorer);
        dw_ext->setObjectName(QStringLiteral("dw_ext"));
        dw_ext->setFloating(false);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        dw_ext->setWidget(dockWidgetContents_2);
        FileExplorer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dw_ext);
        ownershipChartDockWidget = new QDockWidget(FileExplorer);
        ownershipChartDockWidget->setObjectName(QStringLiteral("ownershipChartDockWidget"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        ownershipChartDockWidget->setWidget(dockWidgetContents_3);
        FileExplorer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), ownershipChartDockWidget);
        informationDockWidget = new QDockWidget(FileExplorer);
        informationDockWidget->setObjectName(QStringLiteral("informationDockWidget"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        informationDockWidget->setWidget(dockWidgetContents_4);
        FileExplorer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), informationDockWidget);
        permissionsDockWidget = new QDockWidget(FileExplorer);
        permissionsDockWidget->setObjectName(QStringLiteral("permissionsDockWidget"));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        permissionsDockWidget->setWidget(dockWidgetContents_5);
        FileExplorer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), permissionsDockWidget);
        chart_widget = new QDockWidget(FileExplorer);
        chart_widget->setObjectName(QStringLiteral("chart_widget"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QStringLiteral("dockWidgetContents_6"));
        chart_widget->setWidget(dockWidgetContents_6);
        FileExplorer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), chart_widget);

        menuBar->addAction(menuAdvanced->menuAction());
        menuAdvanced->addAction(actionCheck_Disk_Fragmentation);
        menuAdvanced->addAction(actionCheck_Security_Threats);

        retranslateUi(FileExplorer);

        QMetaObject::connectSlotsByName(FileExplorer);
    } // setupUi

    void retranslateUi(QMainWindow *FileExplorer)
    {
        FileExplorer->setWindowTitle(QApplication::translate("FileExplorer", "FileExplorer", 0));
        actionCheck_Disk_Fragmentation->setText(QApplication::translate("FileExplorer", "Check Disk Fragmentation", 0));
        actionCheck_Security_Threats->setText(QApplication::translate("FileExplorer", "Check Security Threats", 0));
        menuAdvanced->setTitle(QApplication::translate("FileExplorer", "Advanced", 0));
    } // retranslateUi

};

namespace Ui {
    class FileExplorer: public Ui_FileExplorer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEEXPLORER_H
