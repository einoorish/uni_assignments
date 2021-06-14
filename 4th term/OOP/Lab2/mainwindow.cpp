#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->input->insertPlainText("1 3 3 4\n0 -1 7 8\n0 1 11 12\n0 1 15 16");
    ui->freeVars->insertPlainText("1 2 3 0");
    strategy = Strategy::Strategies::Kramer;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculate_pressed()
{
    QStringList input = ui->input->toPlainText().split("\n");

    //reading matrix------------------------
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

    double **data = new double*[rowsNumber];
    for(int i =0 ; i < rowsNumber; i++){
        data[i]=new double[columnsNumber];
        for(int j = 0; j < columnsNumber; j++){
            data[i][j] = matrix[i][j];
            std::cout << data[i][j] << " ";

        }
        std::cout << std::endl;
    }

    //reading free vars-----------------------
    double* freeVars = new double[columnsNumber];
    int i = 0;
    foreach(QString val, ui->freeVars->toPlainText().split(" ")){
        bool check = false;
        double colValue = val.toDouble(&check);
        if(check){
            freeVars[i++] = colValue;
        }
    }

   ui->result->clear();
   QString result_str;
   double* result;
   try{
       result = Strategy::solvingMethod(strategy, Matrix(data, freeVars, rowsNumber, columnsNumber));
       for(int i = 0; i < columnsNumber; i++){
           result_str.append(QString::number(result[i]));
           result_str.append(" ");
        }
   } catch (char const* message){
       result_str = QString::fromStdString(message);
   }

   ui->result->insert(result_str);
}

void MainWindow::on_radioButton_clicked()
{
    strategy = Strategy::Strategies::Kramer;
}

void MainWindow::on_radioButton_2_clicked()
{
    strategy = Strategy::Strategies::Jacobi;
}

void MainWindow::on_radioButton_3_clicked()
{
    strategy = Strategy::Strategies::Method3;
}
