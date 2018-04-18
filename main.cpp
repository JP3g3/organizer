#include "kalendarz.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    kalendarz w;
    w.show();

    return a.exec();
}
