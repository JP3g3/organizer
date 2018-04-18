#ifndef KALENDARZ_H
#define KALENDARZ_H

#include <QDialog>
#include <QMessageBox>
#include <QFile>
#include <QList>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <spotkanie.h>
#include <zdarzenie.h>

namespace Ui {
class kalendarz;
}

class kalendarz : public QDialog
{
    Q_OBJECT

public:
    explicit kalendarz(QWidget *parent = 0);
    ~kalendarz();

private slots:
    void on_cw_kalendarz_selectionChanged();

    void on_pb_dodaj_clicked();

    void on_pb_edytuj_clicked();

    void on_pb_usun_clicked();

    void on_pb_pokaz_clicked();

    void on_lw_spotkania_itemSelectionChanged();

private:
    Ui::kalendarz *ui;
    QList<zdarzenie> lista_spotkan;
    QList<zdarzenie> list_tmp;

    void odczyt_z_pliku();
    void set_list_widget();
    void refresh();
    void sort_list_tmp();
};

#endif // KALENDARZ_H
