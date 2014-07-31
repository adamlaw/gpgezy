#ifndef GPGEZY_H
#define GPGEZY_H

#include <QObject>
#include <QtCrypto>
#include <memory>

class Gpgezy : public QObject
{
    Q_OBJECT
public:
    explicit Gpgezy(QObject *parent = 0);
public Q_SLOTS:
    void showUsage();
    void doWork(const QStringList& args);
    void start();
    bool checkIsKeyFileKeyringAndAddifNot(const QString& fileName);
    bool checkIsKeyInKeyringAndAddifNot(const QString& keyId);
private:
    void setReturnStatus(int status);
    std::auto_ptr<QCA::KeyStoreManager> spMasterManager_;
};

#endif // GPGEZY_H
