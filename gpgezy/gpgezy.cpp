#include "gpgezy.h"
#include "constants.h"
#include "environment.h"
#include <memory>
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QtCrypto>
#include <QDebug>

Gpgezy::Gpgezy(QObject *parent) :
    QObject(parent)
{
    QDir dataDir(Environment::getDataDirectory());

    if (!dataDir.exists()) {
        if (!dataDir.mkdir(dataDir.absolutePath()))
            qDebug() << "Can't create data dir";
    }
}

void Gpgezy::showUsage()
{
    qDebug() << "--addkey key file name" << endl
             << "--encrypt file names  --keyid your key id or --keyname key file name" << endl
             << "--decrypt file names" << endl
             << "--export-key --keyid your key id --keyname key file name, key type --public or --private" << endl
             << "--create-key";
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

            checkIsKeyFileKeyringAndAddifNot(fileName, true);
            setReturnStatus(EXIT_CODE_SUCCESS);
        } // --addkey

        else if (*current == "--encrypt") {
            ++ current;

            if (current == args.end())
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

            QStringList files;
            QString keyId;
            QString keyFileName;
            QCA::KeyStoreEntry store_entry;
            QCA::KeyStoreManager *ksm = new QCA::KeyStoreManager(this);
            ksm->start();
            ksm->waitForBusyFinished();

            while (current != args.end()) {

                if (*current == "--keyname") {
                    ++ current;

                    if (current == args.end())
                        setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

                    if (QFileInfo(*current).exists())
                        keyFileName = *current;

                    else {
                        qDebug() << "File " << *current << "not exists";
                        setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
                    }
                }

                else if (*current == "--keyid") {
                    ++ current;

                    if (current == args.end())
                        setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

                    keyId = *current;
                }

                else {
                    if (QFileInfo(*current).exists())
                        files << *current;
                    else {
                        qDebug() << "File " << *current << "not exists";
                        setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
                    }
                }

                ++ current;
            }

            if (files.isEmpty())
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);

            QCA::KeyStore key_store( QString("qca-gnupg"), ksm );

            if (keyId.isEmpty() && !keyFileName.isEmpty()) {

                QCA::PGPKey key(keyFileName);

                if (!key.isNull()) {
                    QCA::PGPKey(keyFileName);
                    keyId = key_store.writeEntry(key);
                }
                else
                    qDebug() << "Key from" << keyFileName << "is null";
            }

            Q_FOREACH(const QCA::KeyStoreEntry store_key,  key_store.entryList()) {

                if (store_key.id() == keyId) {
                    store_entry = store_key;
                    break;
                }
            }

            if (store_entry.isNull()) {
                qDebug() << "Key" << *current << "not found";
                setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
            }

            for (current = files.begin(); current != files.end(); ++ current) {
                QFile file(*current);
                QString outputFileName = QFileInfo(*current).absolutePath() + QDir::separator() + QFileInfo(*current).fileName() + ".gpg";

                if (file.open(QIODevice::ReadOnly)) {
                    QCA::SecureMessageKey to;
                    to.setPGPPublicKey(store_entry.pgpPublicKey());
                    to.setPGPSecretKey(store_entry.pgpSecretKey());
                    QCA::OpenPGP pgp;
                    QCA::setProperty("pgp-always-trust", true);
                    QCA::SecureMessage msg(&pgp);
                    msg.setRecipient(to);
                    msg.setFormat(QCA::SecureMessage::Binary);
                    msg.startEncrypt();
                    msg.update(file.readAll());
                    msg.end();
                    msg.waitForFinished(-1);

                    if (msg.success()) {
                        QFile outputFile(outputFileName);

                        if (outputFile.open(QIODevice::WriteOnly)) {
                            outputFile.write(msg.read());
                            outputFile.flush();
                        }
                        else
                            qDebug() << "Can't open file" << outputFileName << "for write";
                    }
                    else
                        qDebug() << "Ecryption error:" << msg.diagnosticText();
                }

                else
                    qDebug() << "Can't open file" << *current << "for read";
            }

            setReturnStatus(EXIT_CODE_SUCCESS);

        } // —encrypt

        else if (*current == "--decrypt") {

        } // --decrypt

        else if (*current == "--export-key") {

        } // --export-key

        else if (*current == "--create-key") {

        } // --create-key
    }

    setReturnStatus(EXIT_CODE_INVALID_ARGUMENT);
}

void Gpgezy::start()
{
    doWork(qApp->arguments());
}

QString Gpgezy::checkIsKeyFileKeyringAndAddifNot(const QString& fileName, bool showMessageIfKeyAlreadyAdded)
{
    QCA::PGPKey key(fileName);

    if (key.isNull())
        return QString();

    QCA::KeyStoreManager::start();
    QCA::KeyStoreManager ksm(this);
    ksm.waitForBusyFinished();
    QCA::KeyStore key_store( QString("qca-gnupg"), &ksm );

    Q_FOREACH(const QCA::KeyStoreEntry store_key,  key_store.entryList()) {

        if (store_key.id() == key.keyId()) {

            if (showMessageIfKeyAlreadyAdded)
                qDebug() << "Key" << key.keyId() << "already added";

            return key.keyId();
        }
    }

    QString str = key_store.writeEntry(key);

    if (!str.isEmpty())
        qDebug() << "Key "  << str << "successfully added";

    return str;
}

// pivate members

void Gpgezy::setReturnStatus(int status)
{
    if (status != EXIT_CODE_SUCCESS)
        showUsage();

    exit(status);
}
