#include "notewindow.h"
#include "ui_notewindow.h"

NoteWindow::NoteWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NoteWindow)
{
    ui->setupUi(this);

    if(Note::currentNote!=nullptr){
        setWindowTitle(Note::currentNote->title);
        ui->textEdit->setText(Note::currentNote->text);
        if(Note::currentNote->category == "Work"){
            ui->work->setChecked(true);
        }else if(Note::currentNote->category == "Personal"){
            ui->personal->setChecked(true);
        }else if(Note::currentNote->category == "Studying"){
            ui->studying->setChecked(true);
        }
    } else {
        ui->textEdit->setText("");
        ui->work->setChecked(false);
        ui->personal->setChecked(false);
        ui->studying->setChecked(false);
    }
}

NoteWindow::~NoteWindow(){
    delete ui;
}

void NoteWindow::on_actionSave_triggered(){
    QString category;
    QString text = ui->textEdit->toPlainText();
    QDateTime time = QDateTime::currentDateTime();

    //TODO: use an enum or something...
    if(ui->personal->isChecked()){
        category = "Personal";
    } else if(ui->work->isChecked()){
        category = "Work";
    } else if(ui->studying->isChecked()){
        category = "Studying";
    }


    if(Note::currentNote==nullptr){
        QString title = QInputDialog::getText(this, "Saving...","Enter file name");
        Note::currentNote = new Note(title, text, category, time);
        setWindowTitle(Note::currentNote->title);
    } else {
        Note::currentNote->editTime = time;
        Note::currentNote->category = category;
        Note::currentNote->text = text;
    }
}


void NoteWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void NoteWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void NoteWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void NoteWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void NoteWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


