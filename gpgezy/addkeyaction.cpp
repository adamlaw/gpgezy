#include "addkeyaction.h"
#include <QFileInfo>
#include <QDebug>
#include <QSqlDriver>
#include "environment.h"

AddKeyAction::AddKeyAction(QObject *parent)
    : AbstractCommandLineAction(parent)
{
}

int AddKeyAction::execute(const QStringList& args)
{
    QString res;

    qDebug() << Q_FUNC_INFO << "args == " << args;
    return 0;
}
