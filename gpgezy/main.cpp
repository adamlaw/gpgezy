#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "gpgezy.h"
#include "constants.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    a.setApplicationName("GPGEzy");
    Gpgezy* gpgezy = new Gpgezy(&a);;
    QTimer::singleShot(0, gpgezy, SLOT(start()));
    return a.exec();
}
