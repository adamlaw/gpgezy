#include "pgpkey.h"

PGPKey::PGPKey()
{
}

QString PGPKey::uid() const
{
    if (!uids_.isEmpty())
        return uids_.first();

    return QString();
}
