#ifndef ABSTRACTCOMMANDLINEACTION_H
#define ABSTRACTCOMMANDLINEACTION_H

#include <QObject>

class QStringList;

class AbstractCommandLineAction : public QObject
{
    Q_OBJECT
public:
    explicit AbstractCommandLineAction(QObject *parent = 0);

Q_SIGNALS:
    void finished();
public Q_SLOTS:
    virtual void execute(const QStringList& args) = 0;
protected:
    virtual void finishAction();
};

#endif // ABSTRACTCOMMANDLINEACTION_H
