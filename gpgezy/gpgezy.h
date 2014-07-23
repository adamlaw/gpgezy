#ifndef GPGEZY_H
#define GPGEZY_H

#include <QObject>

class Gpgezy : public QObject
{
    Q_OBJECT
public:
    explicit Gpgezy(QObject *parent = 0);
public Q_SLOTS:
    void showUsage();
    void start();
Q_SIGNALS:
    void finished();
protected:
    virtual void finishWork();
private:
};

#endif // GPGEZY_H
