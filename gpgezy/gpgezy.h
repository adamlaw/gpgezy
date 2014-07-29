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
    void doWork(const QStringList& cmdline);
    void start();
protected Q_SLOTS:
    virtual void finishWork(int exitCode = 0);
    virtual void setReturnStatus(int status);
private:
    std::auto_ptr<QCA::KeyStoreManager> spMasterManager_;
};

#endif // GPGEZY_H
