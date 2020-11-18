#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QVector>
#include <QStandardItemModel>
#include <QDebug>

#include "note.h"
#include "note_edit_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addNoteToList(Note* note, QStandardItemModel *model);

    void readNotesFromFile(QString fileName, QStandardItemModel *model);
    void readNotesWithCategory(QString category, QStandardItemModel *model);

    void writeNotesDataToFile(QString fileName, QVector<Note*>& list);
    void writeNotesTextToFiles();

    int getNotePositionInFile(int left, int right, Note& note);

private slots:

    void on_add_note_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_open_btn_clicked();

    void on_delete_btn_clicked();

private:
    Ui::MainWindow *ui;

    QVector<Note*> notes;
    QStandardItemModel *main_model;

    NoteEditDialog noteWindow;
};
#endif // MAINWINDOW_H
