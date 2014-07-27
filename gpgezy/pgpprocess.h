#ifndef PGPPROCESS_H
#define PGPPROCESS_H

#include <QObject>
#include <QPointer>

class PGPKey;
class QProcess;

class PGPProcess : public QObject
{
    Q_OBJECT
public:
    explicit PGPProcess(QObject *parent = 0);
public Q_SLOTS:
    // function doesn't check for file existence
    void readKeyFromFile(const QString& fileName, PGPKey& key);
    // function doesn't check for file existence
    void encryptFile(const QString& fileName, const PGPKey& _public, const PGPKey& _private);	
private:
    void initProcess();
    void parseKeyInfo(const QString& info, PGPKey &key);	

    QPointer<QProcess> process_;
};

#endif // PROCESS
