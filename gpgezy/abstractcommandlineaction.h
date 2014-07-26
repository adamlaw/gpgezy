#ifndef ABSTRACTCOMMANDLINEACTION_H
#define ABSTRACTCOMMANDLINEACTION_H

#include <QString>

class QStringList;

class AbstractCommandLineAction
{
public:
    explicit AbstractCommandLineAction();
    QString keyFileById(const QString& id);
    virtual int execute(const QStringList& args) = 0;
};

#endif // ABSTRACTCOMMANDLINEACTION_H
