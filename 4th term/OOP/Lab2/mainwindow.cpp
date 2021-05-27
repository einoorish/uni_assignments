#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculate_pressed()
{
    QStringList input = ui->input->toPlainText().split("\n");

    QList<QList<double>> matrix;
    int rowsNumber = 0; int columnsNumber = 0;

    foreach(QString row, ui->input->toPlainText().split("\n")){
        rowsNumber++;
        QList<double> cols;
        foreach(QString val, row.split(" ")){
            bool check = false;
            double colValue = val.toDouble(&check);
            if(check)
                cols << colValue;
        }

        if(!cols.isEmpty())
            matrix << cols;
        columnsNumber = cols.size();
    }

    std::cout<<rowsNumber;
    //double* result = Strategy::solvingMethod(0, matrix.toStdList(), rowsNumber, columnsNumber);
    QString res;
    for(int i=0; i<matrix.at(1).size(); i++){
        res += QString::number(matrix.at(1).at(i),'f', 2);
        std::cout<<res.toUtf8().constData();
        if(i<res.size()-1)
            res += "," ;
    }

    ui->result->insert(res);
}
