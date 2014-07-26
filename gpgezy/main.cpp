#include <QCoreApplication>
#include <QTimer>
#include <QtCrypto>
#include <QDebug>
#include "gpgezy.h"
#include "constants.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCA::init();		

    if (!QCA::isSupported("openpgp")) {
		qDebug() << QCA::pluginDiagnosticText();
        qWarning() << QObject::tr("openpgp is not supported");
        return EXIT_CODE_OPENPGP_IS_NOT_SUPORTED;
    }

    a.setApplicationName("GPGEzy");
    Gpgezy* gpgezy = new Gpgezy(&a);;
    QTimer::singleShot(0, gpgezy, SLOT(start()));
    return a.exec();
}
