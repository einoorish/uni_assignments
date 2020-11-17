#include "note_edit_dialog.h"
#include "ui_note_edit_dialog.h"
#include <QDebug>

NoteEditDialog::NoteEditDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NoteWindow)
{
    ui->setupUi(this);
}

NoteEditDialog::~NoteEditDialog(){
    delete ui;
}

void NoteEditDialog::on_actionSave_triggered(){
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


void NoteEditDialog::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void NoteEditDialog::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void NoteEditDialog::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void NoteEditDialog::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void NoteEditDialog::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void NoteEditDialog::showEvent(QShowEvent *event)
{
    qDebug() << "SHOW";
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
        setWindowTitle("New note");
        ui->textEdit->setText("");
        ui->work->setChecked(false);
        ui->personal->setChecked(false);
        ui->studying->setChecked(false);
    }
}
