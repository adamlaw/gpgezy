#include "actionsfactory.h"
#include <cstddef>
#include <QString>
#include "addkeyaction.h"
#include "encryptcommand.h"

ActionsFactory::ActionsFactory()
{}

AbstractCommandLineAction* ActionsFactory::createAction(const QString& key)
{
    if (key == "--add-key")
        return new AddKeyAction();

    if (key == "--encrypt")
        return new EncryptCommand();

    return NULL;
}
