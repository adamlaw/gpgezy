#include "addkeyaction.h"
#include <QFileInfo>
//#include <QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlError>
//#include <QSqlRecord>
#include <QtCrypto>
#include <QDebug>
#include "constants.h"

AddKeyAction::AddKeyAction()
{
}

int AddKeyAction::execute(const QStringList& args)
{
    // if no key file path then exit with EXIT_CODE_INVALID_ARGUMENT
    if (args.length() > 1) {

        for (QStringList::const_iterator current = ++ args.begin(); current != args.end(); ++ current) {
            QFileInfo info(*current);

            if (info.exists()) {
                QCA::PGPKey key(*current);

                if (!key.isNull()) {
                    QCA::KeyStoreManager::start();
                    QCA::KeyStoreManager ksm;
                    //ksm.waitForBusyFinished();
                    //QCA::KeyStore pgpks( QString("qca-gnupg"), &ksm );

                    /*Q_FOREACH(QCA::KeyStoreEntry kse, pgpks.entryList()) {
                        QString text = kse.name()+" "+kse.id();
                        QVariant v; v.setValue(kse);
                        qDebug() << "text == " << text;
                    }*/
                } else
                    qDebug() << "Key is null!";
            }

            else {
                qWarning() << "File" << info.absoluteFilePath() << "not exists";
                break;
            }
        }

        return EXIT_CODE_SUCCESS;
    }

    return EXIT_CODE_INVALID_ARGUMENT;
}
