#include <QCoreApplication>
#include <QTimer>
#include "gpgezy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Gpgezy* gpgezy = new Gpgezy(&a);
    QObject::connect(gpgezy, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, gpgezy, SLOT(start()));
    return a.exec();
}
