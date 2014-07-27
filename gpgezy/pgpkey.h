#ifndef PGPKEY_H
#define PGPKEY_H

#include <QStringList>
#include <QByteArray>
#include <QTemporaryFile>
#include <memory>

class PGPKey
{
public:
    friend class PGPProcess;

    PGPKey();
    PGPKey(const QString& fileName);
    QString toByteArray() const;
    void loadFromArray(const QByteArray& data);
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
    std::auto_ptr<QTemporaryFile> tmpFile_;
};

#endif // PGPKEY_H
