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
{/*
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

    ui->result->insert(res);*/
    double **temp_data = new double *[4];
       for(int i = 0; i < 4; ++i)
           temp_data[i] = new double [4];
       temp_data[0][0]=1;
       temp_data[0][1]=3;
       temp_data[0][2]=3;
       temp_data[0][3]=4;
       temp_data[1][0]=0;
       temp_data[1][1]=-1;
       temp_data[1][2]=7;
       temp_data[1][3]=8;
       temp_data[2][0]=0;
       temp_data[2][1]=1;
       temp_data[2][2]=11;
       temp_data[2][3]=12;
       temp_data[3][0]=0;
       temp_data[3][1]=1;
       temp_data[3][2]=15;
       temp_data[3][3]=16;
       double* row=new double [4];
       row[0]=1;
       row[1]=2;
       row[2]=3;
       row[3]=0;
       Matrix mat(temp_data,row,4,4);
       double a=mat.determinant();
       std::cout<<a;

       double* result = Strategy::solvingMethod(Strategy::Strategies::Kramer, mat);
       QString result_str;
       for(int i = 0; i < 4; i++){
          result_str.append(QString::number(result[i]));
          result_str.append(" ");
       }

       ui->result->insert(result_str);
}
