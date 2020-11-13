#include "note.h"

Note::Note(){}

Note::Note(QString title, QString text, QString category, QDateTime time) : title(title), text(text), category(category), editTime(time){};


QString Note::dateToFileName(QDateTime editTime)
{
    QString fileName = "";
    fileName.append(editTime.date().toString("dd.MM.yyyy"));
    fileName.append("_");
    fileName.append(editTime.time().toString("hh.mm.ss") + ".txt");
    return fileName;
}
