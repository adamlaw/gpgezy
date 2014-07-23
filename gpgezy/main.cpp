#include <QCoreApplication>
#include <QTimer>
#include "gpgezy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("gpgezy");
    Gpgezy* gpgezy = new Gpgezy(&a);;
    QTimer::singleShot(0, gpgezy, SLOT(start()));
    return a.exec();
}
