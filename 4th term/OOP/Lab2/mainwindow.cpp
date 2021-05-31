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



    double* result = Strategy::solvingMethod(Strategy::Strategies::Kramer, Matrix(data, freeVars, rowsNumber, columnsNumber));

       /*double **temp_data = new double *[4];
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
       */

       QString result_str;
       for(int i = 0; i < 4; i++){
          result_str.append(QString::number(result[i]));
          result_str.append(" ");
       }

       ui->result->insert(result_str);
}
