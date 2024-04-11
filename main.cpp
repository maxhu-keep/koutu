#include "cutout.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CutOut w;
    w.show();
    return a.exec();
}
