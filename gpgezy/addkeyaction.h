#ifndef ADDKEYACTION_H
#define ADDKEYACTION_H

#include "abstractcommandlineaction.h"

class AddKeyAction : public AbstractCommandLineAction
{
    Q_OBJECT
public:
    AddKeyAction(QObject* parent = 0);
public Q_SLOTS:
    virtual int execute(const QStringList& args);
};

#endif // ADDKEYACTION_H
