#ifndef GPGEZY_H
#define GPGEZY_H

#include <QObject>
#include "actionsfactory.h"
#include <memory>

class QSqlDatabase;

class Gpgezy : public QObject
{
    Q_OBJECT
public:
    explicit Gpgezy(QObject *parent = 0);
public Q_SLOTS:
    void showUsage();
    void start();
protected Q_SLOTS:
    virtual void finishWork(int exitCode = 0);
private:
    void createWorkingEnvirnment();
    void createTables(QSqlDatabase& db);
    void showWarningAndFinish(const QString& warning, int exitCode);

    std::auto_ptr<ActionsFactory> factory_;
};

#endif // GPGEZY_H
