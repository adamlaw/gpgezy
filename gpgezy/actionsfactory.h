#ifndef ACTIONSFACTORY_H
#define ACTIONSFACTORY_H

class AbstractCommandLineAction;
class QObject;
class QString;

class ActionsFactory
{
public:
    static AbstractCommandLineAction* createAction(const QString& key, QObject* parent = 0);
};

#endif // ACTIONSFACTORY_H
