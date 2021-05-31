#include "mainwindow.h"
#include <iostream>
#include <QApplication>

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//    double **temp_data = new double *[4];
//       for(int i = 0; i < 4; ++i)
//           temp_data[i] = new double [4];
//       temp_data[0][0]=1;
//       temp_data[0][1]=3;
//       temp_data[0][2]=3;
//       temp_data[0][3]=4;
//       temp_data[1][0]=0;
//       temp_data[1][1]=-1;
//       temp_data[1][2]=7;
//       temp_data[1][3]=8;
//       temp_data[2][0]=0;
//       temp_data[2][1]=1;
//       temp_data[2][2]=11;
//       temp_data[2][3]=12;
//       temp_data[3][0]=0;
//       temp_data[3][1]=1;
//       temp_data[3][2]=15;
//       temp_data[3][3]=16;
//       double* row=new double [4];
//       row[0]=1;
//       row[1]=2;
//       row[2]=3;
//       row[3]=0;
//       Matrix mat(temp_data,row,4,4);
//       double a=mat.determinant();
//       std::cout<<a;

//       double* result = Strategy::solvingMethod(0, mat);
//       for(int i = 0; i < 4; i++){
//           std::cout << temp_data[i][0];
//       }

       return 1;
}

