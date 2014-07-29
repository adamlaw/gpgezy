#include "actionsfactory.h"
#include <cstddef>
#include <QString>
#include "addkeyaction.h"
#include "encryptcommand.h"
#include "decryptcommand.h"

ActionsFactory::ActionsFactory()
{}

AbstractCommandLineAction* ActionsFactory::createAction(const QString& key)
{
    if (key == "--addkey")
        return new AddKeyAction();

    if (key == "--encrypt")
        return new EncryptCommand();

    if (key == "--decrypt")
        return new DecryptCommand();

    return NULL;
}
