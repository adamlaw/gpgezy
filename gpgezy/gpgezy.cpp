#include "gpgezy.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include "actionsfactory.h"
#include "abstractcommandlineaction.h"
#include <iostream>
#include <QDebug>

Gpgezy::Gpgezy(QObject *parent) :
    QObject(parent)
{
}

void Gpgezy::showUsage()
{

}

void Gpgezy::start()
{
    QStringList args = qApp->arguments();

    if (args.length() >= 1) {
        AbstractCommandLineAction* action = ActionsFactory::createAction(* (++ args.begin()), this);

        if (action != NULL) {
            connect(action, SIGNAL(finished()), this, SIGNAL(finished()));
            action->execute(args);
        } else
            qDebug() << tr("Unrecognized command");
    } else
        showUsage();

    finishWork();
}

void Gpgezy::finishWork()
{
    qDebug() << "emit finished";
    Q_EMIT finished();
}
