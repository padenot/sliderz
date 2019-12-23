#include "sliderz.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Sliderz w;
    w.show();
    return a.exec();
}
