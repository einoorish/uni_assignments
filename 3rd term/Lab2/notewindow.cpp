#include "notewindow.h"
#include "ui_notewindow.h"

NoteWindow::NoteWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NoteWindow)
{
    ui->setupUi(this);
    //TODO: set window title to note title
}

NoteWindow::~NoteWindow(){
    delete ui;
}


void NoteWindow::on_actionNew_triggered(){
     currentFile.clear();
     ui->textEdit->setText(QString());
}

void NoteWindow::on_actionOpen_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(fileName);

    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);

    QTextStream in(&file); // to read from file
    QString text = in.readAll();

    ui->textEdit->setText(text);

    file.close();
}

void NoteWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    currentFile = fileName;

    setWindowTitle(fileName);

    QTextStream out(&file);

    QString text = ui->textEdit->toPlainText();
    out << text;

    file.close();
}

void NoteWindow::on_actionSave_triggered(){
    if(currentFile.isEmpty())
        currentFile = QFileDialog::getSaveFileName(this, "Save");

    QFile file(currentFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
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

