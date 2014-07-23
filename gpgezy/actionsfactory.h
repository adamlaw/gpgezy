#ifndef ACTIONSFACTORY_H
#define ACTIONSFACTORY_H

class AbstractCommandLineAction;
class QObject;
class QString;

class ActionsFactory
{
public:
    ActionsFactory();
    AbstractCommandLineAction* createAction(const QString& key, QObject* parent = 0);
};

#endif // ACTIONSFACTORY_H
