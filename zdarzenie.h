#ifndef ZDARZENIE_H
#define ZDARZENIE_H

#include <QDate>
class zdarzenie
{
public:
    int id;
    QDate data;
    QTime godzina;
    QString temat;
    QString opis;

    zdarzenie();

    QString toString();
};

#endif // ZDARZENIE_H
