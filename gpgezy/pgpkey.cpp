#include "pgpkey.h"
#include "pgpprocess.h"
#include <QFile>
#include <QDebug>

PGPKey::PGPKey()
{
}

PGPKey::PGPKey(const QString& fileName)
    : fileName_(fileName)
{
    PGPProcess process;
    process.readKeyFromFile(fileName, * const_cast<PGPKey*> (this));
}

QString PGPKey::toByteArray() const
{
    if (!fileName_.isEmpty()) {

        QFile file(fileName_);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            return file.readAll();
        else
            qWarning() << "PGPKey: can't open file " << fileName_ << " for read";
    }

    return QByteArray();
}
