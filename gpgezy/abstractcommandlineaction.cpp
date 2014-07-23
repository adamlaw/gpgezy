#include "abstractcommandlineaction.h"

AbstractCommandLineAction::AbstractCommandLineAction(QObject *parent) :
    QObject(parent)
{
}

void AbstractCommandLineAction::finishAction(int code)
{
    Q_EMIT finished(code);
}
