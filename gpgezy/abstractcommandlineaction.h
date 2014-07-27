#ifndef ABSTRACTCOMMANDLINEACTION_H
#define ABSTRACTCOMMANDLINEACTION_H

#include <QStringList>

class AbstractCommandLineAction
{
public:
    explicit AbstractCommandLineAction();
    QStringList keysById(const QString& key_id);
    virtual int execute(const QStringList& args) = 0;
};

#endif // ABSTRACTCOMMANDLINEACTION_H
