#include "abstractcommandlineaction.h"
//#include <QSqlDatabase>
//#include <QSqlQuery>
//#include <QSqlRecord>
#include "constants.h"
#include <QDebug>

AbstractCommandLineAction::AbstractCommandLineAction()
{
}

QStringList AbstractCommandLineAction::keysById(const QString& key_id)
{
    /*QSqlDatabase db = QSqlDatabase::database(constants::dbConnectionName);
    QSqlQuery q(db);
    QString sql = "SELECT key_content FROM KEYS where key_id = '%1'";
    QStringList res;

    qDebug() << "sql ==  " << sql.arg(key_id);

    if (q.exec(sql.arg(key_id))) {

        while (q.next())
            res << q.record().value(0).toString();
    }
    else
        qWarning() << "It's a bug!";

    return res;*/
    return QStringList();
}
