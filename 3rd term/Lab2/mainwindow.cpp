#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    catsGif = new QMovie("icons/cats.gif");
//    ui->catsGif->setMovie(catsGif);
//    catsGif->start();


}

MainWindow::~MainWindow(){
    delete ui;
}
