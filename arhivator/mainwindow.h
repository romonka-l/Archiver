#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlistviewexplorermodel.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <string>
#include "archalgs.h"
#include "qlistviewexplorermodel.h"
#include "QDesktopServices"
#include "QUrl"
#include "QMessageBox"
#include "QThread"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    QFileInfoList createFileQueue();

    void archAll(QFileInfo dirInfo);

    void on_recBtn_clicked();

    void on_archBtn_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

    void on_dirUpBtn_clicked();

private:
    Ui::MainWindow *ui;
    QFileInfoList *aDirList;
    QListViewExplorerModel *model;
    QDir currentFolder;
};
#endif // MAINWINDOW_H
