#include "main_window.h"
#include "ui_main_window.h"

QString DATA_PATH = "data/notesData.txt";
QString TEXT_PATH = "data/notesText/";

Note* Note::currentNote = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , main_model(new QStandardItemModel)
{
    ui->setupUi(this);

    ui->listView->setModel(main_model);
    readNotesFromFile(DATA_PATH, main_model);
}

MainWindow::~MainWindow(){
    //saving any changes
    writeNotesDataToFile(DATA_PATH, notes);
    writeNotesTextToFiles();
    delete ui;
}

//----------------------------------------------------------------------SLOTS------------------------------------------------------------------------

void MainWindow::on_add_note_clicked()
{
    Note::currentNote = nullptr;
    qDebug()<<(Note::currentNote?Note::currentNote->title:"EMPTYNOTE!!!");
    noteWindow.exec();

    if(Note::currentNote != nullptr){
        //if "Save" was clicked add note to list
         notes.push_back(Note::currentNote);
         main_model->insertRow(notes.size()-1, new QStandardItem(Note::currentNote->title));
         Note::currentNote = nullptr;
    }

}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->open_btn->setEnabled(true);
    ui->archive_btn->setEnabled(true);
    ui->delete_btn->setEnabled(true);

    Note::currentNote = notes.at(index.row());
    qDebug()<<Note::currentNote->title;
}

void MainWindow::on_open_btn_clicked()
{
    qDebug() << "SELECTED" << ui->listView->currentIndex().row();
    noteWindow.exec();

    notes.insert(ui->listView->currentIndex().row(), Note::currentNote);
        // main_model->setData(ui->listView->currentIndex(), new QStandardItem(Note::currentNote->title));


}


//----------------------------------------------------------------------FILES------------------------------------------------------------------------


void MainWindow::readNotesFromFile(QString fileName, QStandardItemModel *model)
{
    QFile dataNotes(fileName);
    if (!dataNotes.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!dataNotes.atEnd()){
        //read title
        QString title = dataNotes.readLine();
        title.remove(title.size()-1,1);

        //read date
        QString year = dataNotes.readLine();
        QString month = dataNotes.readLine();
        QString day = dataNotes.readLine();
        QString hour = dataNotes.readLine();
        QString minute = dataNotes.readLine();
        QString second = dataNotes.readLine();
        QDateTime createTime = QDateTime(QDate(year.toInt(),month.toInt(), day.toInt()),QTime(hour.toInt(),minute.toInt(), second.toInt()));

        //read category
        QString category = dataNotes.readLine();

        //read text
        QString fileName = Note::dateToFileName(createTime);
        QFile textNotes(TEXT_PATH+fileName);
        if (!textNotes.open(QIODevice::ReadOnly | QIODevice::Text))
            return;
        QString text = textNotes.readAll();
        textNotes.close();

        //adding note to list
        Note* newNote = new Note(title, text, category, createTime);
        addNoteToList(newNote, model);
    }

    dataNotes.close();
}


void MainWindow::addNoteToList(Note* note, QStandardItemModel *model)
{
    int position = getNotePositionInFile(0, std::max(0,notes.size()-1), *note);
    notes.insert(notes.begin() + position, note);
    model->insertRow(position, new QStandardItem(note->title));
}

int MainWindow::getNotePositionInFile(int left, int right, Note& note)
{
    if (left == right)
        return left;

    int middle = (left+right)/2;
    if (notes[middle]->editTime > note.editTime)
        getNotePositionInFile(left, middle, note);
    else
        getNotePositionInFile(middle+1, right, note);

    return left;
}


void MainWindow::writeNotesDataToFile(QString fileName, QVector<Note*>& list)
{
    QFile dataNotes(fileName);
    dataNotes.open(QIODevice::WriteOnly);
    QTextStream out(&dataNotes);
    for (int i = 0; i < list.size(); i++)
    {
        out << list[i]->title << "\n";
        out << list[i]->editTime.date().year() << "\n";
        out << list[i]->editTime.date().month() << "\n";
        out << list[i]->editTime.date().day() << "\n";
        out << list[i]->editTime.time().hour() << "\n";
        out << list[i]->editTime.time().minute() << "\n";
        out << list[i]->editTime.time().second() << "\n";
        out << list[i]->category << "\n";
    }
    out.flush();
    dataNotes.close();
}

void MainWindow::writeNotesTextToFiles()
{
    for (int i = 0; i < notes.size(); i++)
    {
        QString fileName = Note::dateToFileName(notes[i]->editTime);
        QFile textNotes(TEXT_PATH+fileName);
        if (!textNotes.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&textNotes);

        out << notes[i]->text;

        out.flush();
        textNotes.close();
    }
}
