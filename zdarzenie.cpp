#include "zdarzenie.h"

zdarzenie::zdarzenie()
{

}

QString zdarzenie::toString()
{
    return godzina.toString("hh:mm") + " " + temat;
}

