#ifndef DECRYPTCOMMAND_H
#define DECRYPTCOMMAND_H

#include "abstractcommandlineaction.h"

class DecryptCommand : public AbstractCommandLineAction
{
public:
    DecryptCommand();
    virtual int execute(const QStringList& args);
};

#endif // DECRYPTCOMMAND_H
