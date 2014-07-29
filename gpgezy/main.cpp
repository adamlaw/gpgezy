#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include "gpgezy.h"
#include "constants.h"
#include <QTextCodec>
#include <QtCrypto>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QCA::Initializer init;

    if (!QCA::isSupported("openpgp")) {
        qDebug() << "OPENPGP is not supported!";
        return EXIT_CODE_OPENPGP_IS_NOT_SUPORTED;
    }

    a.setApplicationName("GPGEzy");
    Gpgezy* gpgezy = new Gpgezy(&a);;
    QTimer::singleShot(0, gpgezy, SLOT(start()));
    return a.exec();
}
