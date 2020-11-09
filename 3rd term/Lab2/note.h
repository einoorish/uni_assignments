#ifndef NOTE_H
#define NOTE_H
#include <QString>
#include <QDateTime>

class Note
{
private:
    int id;
    QString fileName = "";
    QString text = "";
    QString category = "";
    QDateTime editTime;

public:
    friend class MainWindow;
    friend class NoteWindow;
    Note();
    Note(QString& fileName, QString& text, QString& category, QDateTime& time);
};

#endif // NOTE_H
