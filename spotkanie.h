#ifndef SPOTKANIE_H
#define SPOTKANIE_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QList>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include "zdarzenie.h"

namespace Ui {
class spotkanie;
}

class spotkanie : public QDialog
{
    Q_OBJECT

public:
    explicit spotkanie(int _operacja, int _id, QDate _data, QList<zdarzenie> lista_spotkan, QWidget *parent = 0);
    ~spotkanie();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::spotkanie *ui;
    QList<zdarzenie> lista;

    int id;
    int operacja;
    QDate data;

    void getSpotkanie(int id);
    void SaveEdit(int operacja);
    int getLastId();
};

#endif // SPOTKANIE_H
