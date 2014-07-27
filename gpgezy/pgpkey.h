#ifndef PGPKEY_H
#define PGPKEY_H

#include <QStringList>

class PGPKey
{
public:
    friend class PGPProcess;

    PGPKey();
    PGPKey(const QString& fileName);
    QString toByteArray() const;
    bool isPublic() const { return public_; }
    bool isPrivate() const { return !public_; }
    QString keyId() const {  return key_id_; }
    bool isNull() const { return key_id_.isEmpty(); }
    QString uid() const { return uid_ ; }
private:
    bool public_;
    QString key_id_;
    QString fileName_;
    QString uid_;
};

#endif // PGPKEY_H
