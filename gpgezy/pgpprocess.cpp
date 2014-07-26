#include "pgpprocess.h"
#include <QProcess>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include "pgpkey.h"

PGPProcess::PGPProcess(QObject *parent) :
    QObject(parent)
{
}

void PGPProcess::readKeyFromFile(const QString &fileName, PGPKey& key)
{
    initProcess();
    process_->start("pgp", QStringList() << fileName);
    process_->waitForReadyRead();
    process_->waitForFinished();
    parseKeyInfo(QString::fromLocal8Bit(process_->readAll()), key);
}

void PGPProcess::initProcess()
{
    if (process_.isNull())
        process_ = new QProcess(this);
}

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

    while (current ++ != str.end()) {
        if (*current == '/') {

            while (!current->isSpace())
                key.key_id_.append(*current ++);

            break;
        }
    }

    if (key.key_id_.isEmpty())
        qDebug() << "Can't parse key id";
}
