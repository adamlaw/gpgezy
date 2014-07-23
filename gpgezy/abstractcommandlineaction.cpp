#include "abstractcommandlineaction.h"

AbstractCommandLineAction::AbstractCommandLineAction(QObject *parent) :
    QObject(parent)
{
}

void AbstractCommandLineAction::finishAction()
{
    Q_EMIT finished();
}
