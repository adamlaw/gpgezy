#include "addkeyaction.h"
#include <QFileInfo>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QtCrypto>
#include "constants.h"

#include <Windows.h>

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
                QCA::PGPKey key(info.absoluteFilePath().toLatin1());
				OutputDebugString(L"\n\n");

				if (key.isNull())
					OutputDebugString(L"key is null == true");
				else
					OutputDebugString(L"key is null == false");

				OutputDebugString(L"\n\n");

                if (!key.isNull()) {
                    QSqlQuery query(db);

                    //QString sql = "SELECT ALL FROM KEYS WHERE key_id";

                    /*sql = "INSERT INTO KEYS (key, key_id, public) VALUES ('%1', '%2', %3)";
                    QString keyData = key.toString();
                    bool isPublic = keyData.contains("public", Qt::CaseInsensitive);
                    sql = sql.arg(keyData).arg(key.keyId()).arg(isPublic);*/
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
