#include "main_window.h"
#include "ui_main_window.h"

QString MAIN_DATA_PATH = "data/main_notesData.txt";
QString MAIN_TEXT_PATH = "data/main_notesText/";

QString ARCHIVE_DATA_PATH = "data/archive_notesData.txt";
QString ARCHIVE_TEXT_PATH = "data/archive_notesText/";

Note* Note::currentNote = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , main_model(new QStandardItemModel)
    , archive_model(new QStandardItemModel)
{
    ui->setupUi(this);

    ui->listView->setModel(main_model);
    readNotesFromFile(MAIN_DATA_PATH, MAIN_TEXT_PATH, main_model);
    readNotesFromFile(ARCHIVE_DATA_PATH, ARCHIVE_TEXT_PATH, archive_model);
}

MainWindow::~MainWindow(){
    //saving any changes
    writeNotesDataToFile(MAIN_DATA_PATH, main_notes);
    writeNotesDataToFile(ARCHIVE_DATA_PATH, archived_notes);
    writeNotesTextToFiles(MAIN_TEXT_PATH, main_notes);
    writeNotesTextToFiles(ARCHIVE_TEXT_PATH, archived_notes);
    delete ui;
}

//----------------------------------------------------------------------SLOTS------------------------------------------------------------------------

void MainWindow::on_add_note_clicked()
{
    Note::currentNote = nullptr;
    noteWindow.exec();

    if(Note::currentNote != nullptr){
        //if "Save" was clicked add note to list
         main_notes.push_back(Note::currentNote);
         main_model->insertRow(main_notes.size()-1, new QStandardItem(Note::currentNote->title));
         Note::currentNote = nullptr;
    }

}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->open_btn->setEnabled(true);
    ui->archive_btn->setEnabled(true);
    ui->delete_btn->setEnabled(true);

    if(ui->listView->model() == main_model){
        Note::currentNote = main_notes.at(index.row());
    } else
        Note::currentNote = archived_notes.at(index.row());
}

void MainWindow::on_open_btn_clicked()
{
    Note oldNote = *Note::currentNote;

    noteWindow.exec();

    if(oldNote.editTime != Note::currentNote->editTime){
        //"Save" was triggered

        //remove old text
        int index = ui->listView->currentIndex().row();
        QString old_text_file_path;

        if(ui->listView->model() == main_model){
            old_text_file_path = MAIN_TEXT_PATH+Note::dateToFileName(main_notes[index]->editTime);
        } else
            old_text_file_path = ARCHIVE_TEXT_PATH+Note::dateToFileName(archived_notes[index]->editTime);

        QFile old_text_file(old_text_file_path);
        old_text_file.remove();

        if(ui->listView->model() == main_model){
            main_notes.erase(main_notes.begin()+index);
            main_notes.insert(main_notes.begin()+index, Note::currentNote);
        } else {
            archived_notes.erase(archived_notes.begin()+index);
            archived_notes.insert(archived_notes.begin()+index, Note::currentNote);
        }
    }
}

void MainWindow::on_archive_btn_clicked()
{
    int index = ui->listView->currentIndex().row();

    if(ui->listView->model() == main_model){
        QFile file(MAIN_TEXT_PATH+Note::dateToFileName(main_notes[index]->editTime));
        file.remove();

        archived_notes.push_back(main_notes[index]);
        main_notes.erase(main_notes.begin()+index);

        archive_model->insertRow(archived_notes.size()-1, new QStandardItem(archived_notes.last()->title));
        main_model->removeRow(index);
    }
}

void MainWindow::on_delete_btn_clicked()
{
    int index = ui->listView->currentIndex().row();

    if(ui->listView->model() == main_model){
        QFile file(MAIN_TEXT_PATH+Note::dateToFileName(main_notes[index]->editTime));
        file.remove();
        main_notes.erase(main_notes.begin()+index);
        main_model->removeRow(index);
    }else {
        QFile file(ARCHIVE_TEXT_PATH+Note::dateToFileName(archived_notes[index]->editTime));
        file.remove();
        archived_notes.erase(archived_notes.begin()+index);
        archive_model->removeRow(index);
    }

}


void MainWindow::on_main_list_btn_clicked()
{
    ui->listView->setModel(main_model);
}

void MainWindow::on_archive_list_btn_clicked()
{
    ui->listView->setModel(archive_model);
}

//----------------------------------------------------------------------FILES------------------------------------------------------------------------


void MainWindow::readNotesFromFile(QString dataFileName, QString textFolderName, QStandardItemModel *model)
{
    QFile dataNotes(dataFileName);
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
        category.remove(category.size()-1,1);

        //read text
        QString fileName = Note::dateToFileName(createTime);
        QFile textNotes(textFolderName+fileName);
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
    int position;
    if(model == main_model){
        position = getNotePositionInFile(0, std::max(0,main_notes.size()-1), *note, main_notes);
        main_notes.insert(main_notes.begin() + position, note);
    } else {
        position = getNotePositionInFile(0, std::max(0,archived_notes.size()-1), *note, archived_notes);
        archived_notes.insert(archived_notes.begin() + position, note);
    }
    model->insertRow(position, new QStandardItem(note->title));
}

int MainWindow::getNotePositionInFile(int left, int right, Note& note, QVector<Note*>& list)
{
    if (left == right)
        return left;

    int middle = (left+right)/2;

    if (list[middle]->editTime > note.editTime)
        getNotePositionInFile(left, middle, note, list);
    else
        getNotePositionInFile(middle+1, right, note, list);

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

void MainWindow::writeNotesTextToFiles(QString folderName, QVector<Note*>& list)
{
    for (int i = 0; i < list.size(); i++)
    {
        QString fileName = Note::dateToFileName(list[i]->editTime);
        QFile textNotes(folderName+fileName);
        if (!textNotes.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&textNotes);

        out << list[i]->text;

        out.flush();
        textNotes.close();
    }
}


