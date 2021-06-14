#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "strategy.h"
#include <qgroupbox.h>
#include <QRadioButton>

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
    void on_calculate_pressed();

    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Strategy::Strategies strategy;
};
#endif // MAINWINDOW_H
