#include "kalendarz.h"
#include "ui_kalendarz.h"

kalendarz::kalendarz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kalendarz)
{
    ui->setupUi(this);
    ui->pb_edytuj->setEnabled(false);
    ui->pb_pokaz->setEnabled(false);
    ui->pb_usun->setEnabled(false);

    refresh();
}

kalendarz::~kalendarz()
{
    delete ui;
}

void kalendarz::on_cw_kalendarz_selectionChanged()
{
    refresh();
    on_lw_spotkania_itemSelectionChanged();
}

void kalendarz::on_pb_dodaj_clicked()
{
    spotkanie _dodaj(1, 0, ui->cw_kalendarz->selectedDate(), lista_spotkan, this); //QDate::fromString(ui->cw_kalendarz->selectedDate().toString("dd-MM-yyyy"))
    _dodaj.exec();
    refresh();
}

void kalendarz::on_pb_edytuj_clicked()
{
    zdarzenie tmp = list_tmp[ui->lw_spotkania->currentIndex().row()];
    spotkanie _edytuj(2, tmp.id, ui->cw_kalendarz->selectedDate(), lista_spotkan, this);
    _edytuj.exec();
    refresh();
}

void kalendarz::on_pb_usun_clicked()
{
    zdarzenie tmp = list_tmp[ui->lw_spotkania->currentIndex().row()];
    QFile plik("D:\\mobileData\\VI\\qt\\organizator\\dane.txt");
    if(plik.exists())
        if(plik.open(QFile::WriteOnly|QFile::Text)){
            QTextStream zapis(&plik);
            foreach (zdarzenie item, lista_spotkan)
                if (item.id != tmp.id)
                    zapis << item.id << ";" << item.data.toString("dd-MM-yyyy") << ";" << item.godzina.toString("hh:mm") << ";" << item.temat << ";" << item.opis << ";\n";
        }
    refresh();
    on_lw_spotkania_itemSelectionChanged();
}

void kalendarz::on_pb_pokaz_clicked()
{
    zdarzenie tmp = list_tmp[ui->lw_spotkania->currentIndex().row()];
    spotkanie _pokaz(3, tmp.id, ui->cw_kalendarz->selectedDate(), lista_spotkan, this);
    _pokaz.exec();
}

void kalendarz::odczyt_z_pliku(){
    QFile plik("D:\\mobileData\\VI\\qt\\organizator\\dane.txt");
    if(plik.exists()){
        if(plik.open(QFile::ReadOnly|QFile::Text)){

            QTextStream odczyt(&plik);
            QString linia;
            QStringList tabLinia;
            zdarzenie dane;

            lista_spotkan.clear();

            while(!odczyt.atEnd()){
                linia = odczyt.readLine();
                tabLinia = linia.split(';');

                dane.id = tabLinia[0].toInt();
                dane.data = QDate::fromString(tabLinia[1], "dd-MM-yyyy");
                dane.godzina = QTime::fromString(tabLinia[2], "hh:mm");
                dane.temat = tabLinia[3];
                dane.opis = tabLinia[4];

                lista_spotkan.append(dane);

            }
        }
    }
}
void kalendarz::set_list_widget(){
    if(lista_spotkan.length() > 0){
        ui->lw_spotkania->clear();
        list_tmp.clear();

        foreach ( zdarzenie item, lista_spotkan)
            if(item.data.toString("dd-MM-yyyy") == ui->cw_kalendarz->selectedDate().toString("dd-MM-yyyy"))
                list_tmp.append(item);

        sort_list_tmp();

        foreach ( zdarzenie item, list_tmp)
            ui->lw_spotkania->addItem(item.toString());

        if (ui->lw_spotkania->count() > 0)
            ui->lw_spotkania->item(0)->setSelected(true);
        ui->lw_spotkania->setFocus();
    }
}

void kalendarz::on_lw_spotkania_itemSelectionChanged()
{
    if (ui->lw_spotkania->count() > 0){
        ui->pb_edytuj->setEnabled(true);
        ui->pb_pokaz->setEnabled(true);
        ui->pb_usun->setEnabled(true);
    }
    else {
        ui->pb_edytuj->setEnabled(false);
        ui->pb_pokaz->setEnabled(false);
        ui->pb_usun->setEnabled(false);
    }
}

void kalendarz::refresh(){
    odczyt_z_pliku();
    set_list_widget();
}

void kalendarz::sort_list_tmp(){
    if (list_tmp.count() > 0){
        bool flaga = false;

        do {
            flaga = false;
            for(int i=(list_tmp.count()-1); 0<i; i--){
                zdarzenie item1 = list_tmp[i -1];
                zdarzenie item2 = list_tmp[i];

                if(item1.godzina > item2.godzina){
                    list_tmp[i -1] = list_tmp[i];
                    list_tmp[i] = item1;
                    flaga = true;
                }

            }
        } while (flaga != false);
    }
}
