#ifndef PGPKEY_H
#define PGPKEY_H

#include <QStringList>

class PGPKey
{
public:
    friend class PGPProcess;

    PGPKey();
    QString uid() const;
    bool isPublic() const { return public_; }
    bool isPrivate() const { return !public_; }
    QString keyId() const {  return key_id_; }
    QStringList uids() const { return uids_; }
private:
    bool public_;
    QString key_id_;
    QStringList uids_;
};

#endif // PGPKEY_H
