#include "pgpprocess.h"
#include <QProcess>
#include <QFileInfo>
#include <QDebug>

PGPProcess::PGPProcess(QObject *parent) :
    QObject(parent)
{
}

void PGPProcess::readKeyFromFile(const QString &fileName, PGPKey& key)
{
    initProcess();
    process_->start("pgp", QStringList() << fileName);
    process_->waitForReadyRead();
	qDebug() << "sdsdsdsd";
    qDebug() << process_->readAll();
	process_->waitForFinished();
}

void PGPProcess::initProcess()
{
    if (process_.isNull())
        process_ = new QProcess(this);
}
