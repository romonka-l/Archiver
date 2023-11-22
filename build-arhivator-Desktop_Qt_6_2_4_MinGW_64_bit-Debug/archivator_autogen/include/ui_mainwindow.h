/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *archBtn;
    QPushButton *recBtn;
    QListView *listView;
    QSpacerItem *horizontalSpacer;
    QPushButton *dirUpBtn;
    QLineEdit *lineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(897, 549);
        MainWindow->setAcceptDrops(true);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("\320\242\321\221\320\274\320\275\320\260\321\217");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/img/main.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        archBtn = new QPushButton(centralwidget);
        archBtn->setObjectName(QString::fromUtf8("archBtn"));

        gridLayout->addWidget(archBtn, 0, 0, 1, 2);

        recBtn = new QPushButton(centralwidget);
        recBtn->setObjectName(QString::fromUtf8("recBtn"));

        gridLayout->addWidget(recBtn, 0, 2, 1, 1);

        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        gridLayout->addWidget(listView, 3, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(672, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        dirUpBtn = new QPushButton(centralwidget);
        dirUpBtn->setObjectName(QString::fromUtf8("dirUpBtn"));
        dirUpBtn->setStyleSheet(QString::fromUtf8("image: url(:/img/folderup.png);"));
        dirUpBtn->setIconSize(QSize(20, 20));

        gridLayout->addWidget(dirUpBtn, 1, 0, 2, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 2, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 897, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(archBtn, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::update));
        QObject::connect(recBtn, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::update));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\220\321\200\321\205\320\270\320\262\320\260\321\202\320\276\321\200", nullptr));
        archBtn->setText(QCoreApplication::translate("MainWindow", "Archive", nullptr));
        recBtn->setText(QCoreApplication::translate("MainWindow", "Recover", nullptr));
        dirUpBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
