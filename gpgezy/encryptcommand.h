#ifndef ENCRYPTCOMMAND_H
#define ENCRYPTCOMMAND_H

#include <abstractcommandlineaction.h>

class EncryptCommand : public AbstractCommandLineAction
{
public:
    EncryptCommand();
    virtual int execute(const QStringList& args);
};

#endif // ENCRYPTCOMMAND_H
