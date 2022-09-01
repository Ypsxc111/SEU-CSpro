#include "logscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogScreen w;
    w.show();

    return a.exec();
}
