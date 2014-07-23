#include "actionsfactory.h"
#include <cstddef>
#include "addkeyaction.h"

ActionsFactory::ActionsFactory()
{

}

AbstractCommandLineAction* ActionsFactory::createAction(const QString& key, QObject* parent)
{
    if (key == "--add-key")
        return new AddKeyAction(parent);

    return NULL;
}
