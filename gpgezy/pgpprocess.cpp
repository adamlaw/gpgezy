#include "pgpprocess.h"
#include <QProcess>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QTemporaryFile>
#include "pgpkey.h"

#define PROGRAM_NAME "gpg"

PGPProcess::PGPProcess(QObject *parent) :
    QObject(parent)
{
}

void PGPProcess::readKeyFromFile(const QString &fileName, PGPKey& key)
{
    initProcess();
    process_->start(PROGRAM_NAME, QStringList() << fileName);
    process_->waitForReadyRead();
    process_->waitForFinished();
    parseKeyInfo(QString::fromLocal8Bit(process_->readAll()), key);
}

void PGPProcess::initProcess()
{
    if (process_.isNull()) {
        process_ = new QProcess(this);
        process_->setProcessChannelMode(QProcess::MergedChannels);
    }
}
// publics slots
void PGPProcess::encryptFile(const QString& fileName, const PGPKey& _public, const PGPKey& _private)
{
    QStringList args;
    args << "--armor" << "--no-default-keyring" << "--always-trust";

    if  (!_public.isNull())
        args << "--keyring";

    if (!_public.fileName_.isEmpty())
        args << _public.fileName_;

    else {
        // TODO: create temprary file
    }

    if (!_private.isNull())
        args << "--secret-keyring" << _private.fileName_;

    args << "--recipient";

    if (!_public.uid_.isEmpty())
        args << _public.uid_;

    else if (!_private.uid_.isEmpty())
        args << _private.uid_;

    args << "--output" << fileName + ".gpg" << "--encrypt" << fileName;
    qDebug() << "options" << args;

    initProcess();
    process_->start(PROGRAM_NAME, args);
    process_->waitForReadyRead();
    process_->waitForFinished();
    qDebug() << process_->readAll();
}

// Private members

void PGPProcess::parseKeyInfo(const QString& info, PGPKey& key)
{
    QString str = info;

    if (str.startsWith("sec"))
        key.public_ = false;
    else if (str.startsWith("pub"))
        key.public_ = true;
    else
        qDebug() << "Can't parse key type";

    QString::const_iterator current = str.begin();

    while (++ current != str.end()) {

        if (key.key_id_.isEmpty() && *current == '/') {

			++ current;

            while (!current->isSpace())
                key.key_id_.append(*current ++);
        }

        else if (*current == '<') {
            ++ current;

            while (*current != '>')
                key.uid_.append(*current ++ );

        }
    }

    if (key.key_id_.isEmpty())
        qDebug() << "Can't parse key id";

    if (key.uid_.isEmpty())
        qDebug() << "Can't parse uid!";
}
