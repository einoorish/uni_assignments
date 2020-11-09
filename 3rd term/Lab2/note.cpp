#include "note.h"

Note::Note()
{
    editTime.currentDateTime();
}

Note::Note(QString& fileName, QString& text, QString& category, QDateTime& time)
{
    this->fileName = fileName;
    this->text = text;
    this->category = category;
    editTime = time;
}
