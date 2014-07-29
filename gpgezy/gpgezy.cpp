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
        // TODO
}

void Gpgezy::doWork(const QStringList& cmdline)
{

    for (QStringList::const_iterator current = cmdline.begin(); current != cmdline.end(); ++ current) {

        // --addkey
        if (*current == "--addkey") {
            QString fileName = * ++ current;

            if (current == cmdline.end() || fileName.isEmpty()) {
                showUsage();
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
            }

            if (!QFileInfo(fileName).exists()) {
                qDebug() << "File " << fileName << "not exists";
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
            }

            QCA::PGPKey key(fileName);

            if (key.isNull()) {
                qDebug() << "Key is null";
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
            }

            spMasterManager_->start();
            std::auto_ptr<QCA::KeyStoreManager> sp_ksm( new QCA::KeyStoreManager());
            sp_ksm->waitForBusyFinished();
            QCA::KeyStore key_store( QString("qca-gnupg"), sp_ksm.get() );
            QString str = key_store.writeEntry(key);

            if (!str.isEmpty())
                qDebug() << "Key "  << str << "successfully added";


            foreach(const QCA::KeyStoreEntry store_key,  key_store.entryList()) {

                if (store_key.id() == key.keyId()) {
                    qDebug() << "Key already added";
                    break;
                }

            }

            setReturnStatus(EXIT_CODE_SUCCESS);
        } // --addkey
    }
}

void Gpgezy::start()
{
    doWork(qApp->arguments());
}


void Gpgezy::finishWork(int exitCode)
{
    exit(exitCode);
}

void Gpgezy::setReturnStatus(int status)
{
    exit(status);
}
