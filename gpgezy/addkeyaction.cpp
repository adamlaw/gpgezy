#include "addkeyaction.h"
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QtCrypto>
#include <QFile>
#include <QDebug>
#include "constants.h"

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
                QFile file(info.absoluteFilePath());
                file.open(QIODevice::ReadOnly | QIODevice::Text);
                QByteArray data = file.readAll();
                QCA::PGPKey key = QCA::PGPKey::fromArray(data);

                qDebug() << "data " << data;

                if (!key.isNull()) {
                    QSqlQuery query(db);
                    QString sql = "SELECT id FROM KEYS where key_id = '%1'";

                    if (!query.next()) {
                        sql = "INSERT INTO KEYS (key, key_id, public) VALUES ('%1', '%2', %3)";
                        QString keyData = QString::fromLocal8Bit(data);
                        bool isPublic = keyData.contains("public", Qt::CaseInsensitive);
                        sql = sql.arg(keyData).arg(key.keyId()).arg(isPublic);
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
