#ifndef ACTIONSFACTORY_H
#define ACTIONSFACTORY_H

class AbstractCommandLineAction;
class QObject;
class QString;

class ActionsFactory
{
public:
    ActionsFactory();
    AbstractCommandLineAction* createAction(const QString& key);
};

#endif // ACTIONSFACTORY_H
