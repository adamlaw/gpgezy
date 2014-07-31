#include "gpgezy.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include "constants.h"
#include "environment.h"
#include <QDir>
#include <QFile>
#include <QDebug>
#include <algorithm>
#include <QtCore>
#include <memory>

Gpgezy::Gpgezy(QObject *parent) :
    QObject(parent), spMasterManager_(new QCA::KeyStoreManager())
{
}

void Gpgezy::showUsage()
{
    qDebug() << "—addkey key file name" << endl
             << "—encrypt file names  --keyid your key id or --keyname key file name" << endl
             << "—decrypt file names" << endl
             << "—export-key --keyid your key id --keyname key file name, key type --public or --private" << endl
             << "—create-key";
}

void Gpgezy::doWork(const QStringList& args)
{

    for (QStringList::const_iterator current = args.begin(); current != args.end(); ++ current) {

        if (*current == "--addkey") {
            ++ current;

            if (current == args.end())
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

            QString fileName = *current;

            if (current == args.end() || fileName.isEmpty())
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

            if (!QFileInfo(fileName).exists()) {
                qDebug() << "File " << fileName << "not exists";
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
            }

            QCA::PGPKey key(fileName);

            if (key.isNull()) {
                qDebug() << "Key is null";
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
            }

            checkIsKeyFileKeyringAndAddifNot(fileName);
            setReturnStatus(EXIT_CODE_SUCCESS);
        } // --addkey

        else if (*current == "—encrypt") {
            ++ current;

            if (current == args.end())
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

            QStringList files;

            while (current ++ != args.end()) {

                if (*current == "--keyname") {

                }

                else if (*current == "--keyid") {

                }

                else
                    files << *current;
            }

        } // —encrypt

        else if (*current == "--decrypt") {

        } // --decrypt

        else if (*current == "--export-key") {

        } // --export-key

        else if (*currnet == "--create-key") {

        } // --create-key
    }

    setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
}

void Gpgezy::start()
{
    doWork(qApp->arguments());
}

bool Gpgezy::checkIsKeyFileKeyringAndAddifNot(const QString& fileName)
{
    QCA::PGPKey key(fileName);

    if (!key.isNull())
        return checkIsKeyInKeyringAndAddifNot(key.keyId());

    return false;
}

bool Gpgezy::checkIsKeyInKeyringAndAddifNot(const QString& keyId)
{
    spMasterManager_->start();
    std::auto_ptr<QCA::KeyStoreManager> sp_ksm( new QCA::KeyStoreManager());
    sp_ksm->waitForBusyFinished();
    QCA::KeyStore key_store( QString("qca-gnupg"), sp_ksm.get() );

    foreach(const QCA::KeyStoreEntry store_key,  key_store.entryList()) {

        if (store_key.id() == keyId) {
            qDebug() << "Key already added";
            return true;
        }
    }

    QString str = key_store.writeEntry(QCA::PGPKey());

    if (!str.isEmpty())
        qDebug() << "Key "  << str << "successfully added";

    return false;
}

// pivate members

void Gpgezy::setReturnStatus(int status)
{
    if (status != EXIT_CODE_SUCCESS)
        showUsage();

    exit(status);
}
