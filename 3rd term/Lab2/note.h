#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDateTime>

class Note
{
private:
    QString title = "";
    QString text = "";
    QString category = "";
    QDateTime editTime;

public:
    friend class MainWindow;
    friend class NoteWindow;
    Note();
    Note(QString fileName, QString text, QString category, QDateTime time);
    static QString dateToFileName(QDateTime time);
    static Note* currentNote;
};


#endif // NOTE_H

