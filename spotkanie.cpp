#include "spotkanie.h"
#include "ui_spotkanie.h"

spotkanie::spotkanie(int _operacje, int _id, QDate _data, QList<zdarzenie> lista_spotkan, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spotkanie)
{
    ui->setupUi(this);

    QString title;
    id = _id;
    data = _data;
    lista = lista_spotkan;
    operacja = _operacje;

    switch(_operacje){
        case 1:
            title = "Nowe";
            ui->te_godzina->setReadOnly(false);
            ui->le_temat->setReadOnly(false);
            ui->pte_opis->setReadOnly(false);
        break;
        case 2:
            title = "Edycja";
            ui->te_godzina->setReadOnly(false);
            ui->le_temat->setReadOnly(false);
            ui->pte_opis->setReadOnly(false);
            getSpotkanie(id);
        break;
        case 3:
            title = "Podgląd";
            ui->te_godzina->setReadOnly(true);
            ui->le_temat->setReadOnly(true);
            ui->pte_opis->setReadOnly(true);
            getSpotkanie(id);
        break;
    }
    setWindowTitle(windowTitle() + "-" + title);
}

spotkanie::~spotkanie()
{
    delete ui;
}

void spotkanie::getSpotkanie(int _id){
    foreach ( zdarzenie item, lista)
        if(item.id == _id){
            ui->te_godzina->setTime(item.godzina);
            ui->le_temat->setText(item.temat);
            ui->pte_opis->setPlainText(item.opis);
        }
}

void spotkanie::SaveEdit(int _operacja){
    if(_operacja == 1 || _operacja == 2) {
        QFile plik("D:\\mobileData\\VI\\qt\\organizator\\dane.txt");
        if(plik.exists())
            if(plik.open(QFile::WriteOnly|QFile::Text)) {
                QTextStream zapis(&plik);

                if (_operacja == 1) {
                    foreach (zdarzenie item, lista)
                        zapis << item.id << ";" << item.data.toString("dd-MM-yyyy") << ";" << item.godzina.toString("hh:mm") << ";" << item.temat << ";" << item.opis << ";\n";
                    zapis << getLastId()+1 << ";" << data.toString("dd-MM-yyyy") << ";" << ui->te_godzina->text() << ";" << ui->le_temat->text() << ";" << ui->pte_opis->toPlainText() << ";\n";
                }

                else {
                    foreach (zdarzenie item, lista) {
                        if (item.id != id)
                            zapis << item.id << ";" << item.data.toString("dd-MM-yyyy") << ";" << item.godzina.toString("hh:mm") << ";" << item.temat << ";" << item.opis << ";\n";
                        else
                            zapis << item.id << ";" << item.data.toString("dd-MM-yyyy") << ";" << ui->te_godzina->text() << ";" << ui->le_temat->text() << ";" << ui->pte_opis->toPlainText()<< ";\n";
                    }
                }
         }
    }
}

int spotkanie::getLastId(){
    return lista[lista.count()-1].id;
}

void spotkanie::on_buttonBox_accepted()
{
    SaveEdit(operacja);
}
