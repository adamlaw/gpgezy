#ifndef ADDKEYACTION_H
#define ADDKEYACTION_H

#include "abstractcommandlineaction.h"

class AddKeyAction : public AbstractCommandLineAction
{
public:
    AddKeyAction();
    virtual int execute(const QStringList& args);
};

#endif // ADDKEYACTION_H
