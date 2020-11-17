#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QInputDialog>
#include <QDateTime>
#include <QCloseEvent>

#include "note.h"

namespace Ui { class NoteWindow; }

class NoteEditDialog: public QDialog
{
    Q_OBJECT
public:
    NoteEditDialog(QWidget *parent = nullptr);
    ~NoteEditDialog();

private slots:

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

private:
    Ui::NoteWindow *ui;

protected:
    void showEvent(QShowEvent *event) override;
};
#endif // NOTEWINDOW_H
