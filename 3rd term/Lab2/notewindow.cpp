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
    currentFile = "";
    delete ui;
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

void NoteWindow::on_actionSave_triggered(){
    if(currentFile.isEmpty()){
        currentFile = QDir::currentPath();
        currentFile += "/";
        currentFile += QInputDialog::getText(this, "Saving...","Enter file name");
        currentFile += ".txt";
    }

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

