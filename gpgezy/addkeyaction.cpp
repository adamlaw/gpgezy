#include "addkeyaction.h"
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include "constants.h"
#include "pgpkey.h"

AddKeyAction::AddKeyAction()
{
}

int AddKeyAction::execute(const QStringList& args)
{
    // if no key file path then exit with EXIT_CODE_INVALID_ARGUMENT
    if (args.length() > 1) {
        QSqlDatabase db = QSqlDatabase::database(constants::dbConnectionName);

        for (QStringList::const_iterator current = ++ args.begin(); current != args.end(); ++ current) {
            QFileInfo info(*current);

            if (info.exists()) {
                PGPKey key(*current);

                if (!key.isNull()) {
                    QSqlQuery query(db);
                    QString sql = "SELECT id FROM KEYS where key = '%1'";
                    query.exec(sql.arg(key.toByteArray()));

                    if (!query.next()) {
                        sql = "INSERT INTO KEYS (key, key_id, public) VALUES ('%1', '%2', %3)";
                        sql = sql.arg(key.toByteArray()).arg(key.keyId()).arg(key.isPublic());
                        query.exec(sql);
                    } else
                        qDebug() << "Key already imported";
                }
            }

            else {
                qWarning() << "File" << info.absoluteFilePath() << "not exists";
                break;
            }
        }

        return EXIT_CODE_SUCCESS;
    }

    return EXIT_CODE_INVALID_ARGUMENT;
}
