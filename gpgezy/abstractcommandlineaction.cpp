#include "abstractcommandlineaction.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>
#include "constants.h"
#include <QDebug>

AbstractCommandLineAction::AbstractCommandLineAction()
{
}

QString AbstractCommandLineAction::keyFileById(const QString& /* id */)
{
    QSqlDatabase db = QSqlDatabase::database(constants::dbConnectionName);
    QSqlQuery q(db);

    if (q.exec("SELECT * FROM KEYS")) {

    }

    return QString();
}
