#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->aDirList = new QFileInfoList();
    this->model = new QListViewExplorerModel();
    this->currentFolder = QDir(QDir::currentPath());
    this->model->getFolderList(this->currentFolder.absolutePath(),this->aDirList);
    this->ui->listView->setModel(model);
    this->ui->lineEdit->setText(QDir::currentPath());
    this->ui->listView->setWrapping(true);
    this->ui->listView->setWordWrap(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QFileInfoList MainWindow::createFileQueue(){
    QDir dir = ui->lineEdit->text();
    QFileInfoList files = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs, QDir::DirsFirst);
    for(int i = 0; i < files.length(); i++){
        if(!files[i].isFile()){
            files.append(((QDir)files[i]
                          .absoluteFilePath())
                          .entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs, QDir::DirsFirst));
        }
    }
    return files;
}

void MainWindow::archAll(QFileInfo dirInfo){
    QFileInfoList files = createFileQueue();
    Archs archs;
    vector<string> stdFiles;
    for(int i = 0; i < files.length(); i++){
        if(files[i].isFile()){
            stdFiles.push_back(files[i].absoluteFilePath().toStdString());
        }
    }
    archs.archDir(stdFiles, ui->lineEdit->text().toStdString(), this->aDirList->at(0).absoluteDir());
}

void MainWindow::on_archBtn_clicked()
{
    Archs archs;
    QFileInfo fileInfo;
    fileInfo.setFile(ui->lineEdit->text());
    if(fileInfo.isDir()){
        archAll(fileInfo);
    } else {
        archs.archLZ78(fileInfo.absoluteFilePath().toStdString(), fileInfo.fileName().toStdString());
    }
    model->getFolderList(this->currentFolder.absolutePath(), this->aDirList);
}

void MainWindow::on_recBtn_clicked()
{
    Archs archs;
    QString strName = ui->lineEdit->text();
    if(strName.endsWith(".zxc")){
        QFileInfo fileInfo;
        fileInfo.setFile(strName);
        if(fileInfo.exists()){
            QMessageBox msgBox;
            msgBox.setText("Файл с таким именем уже существует");
            msgBox.setInformativeText("Желаете переписать?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int res = msgBox.exec();
            if(res == QMessageBox::Cancel){
                return;
            }
        }
        archs.recover(strName.toStdString());
        model->getFolderList(this->currentFolder.absolutePath(), this->aDirList);
    } else {
        QMessageBox::information(0, "Внимание", "Файл не является архивом");
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (this->aDirList->at(index.row()).isDir())
    {
        QString tmp = this->aDirList->at(index.row()).absoluteFilePath();
        this->currentFolder = this->aDirList->at(index.row()).absoluteFilePath();
        model->getFolderList(this->aDirList->at(index.row()).absoluteFilePath(), this->aDirList);
        this->ui->lineEdit->setText(tmp);
    } else {
        QDesktopServices::openUrl(QUrl(this->aDirList->at(index.row()).absoluteFilePath()));
    }
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString tmp = this->aDirList->at(index.row()).absoluteFilePath();
    this->ui->lineEdit->setText(tmp);
}

void MainWindow::on_dirUpBtn_clicked()
{
    currentFolder.cdUp();
    this->ui->lineEdit->setText(currentFolder.absolutePath());
    model->getFolderList(currentFolder.absolutePath(),this->aDirList);
}
