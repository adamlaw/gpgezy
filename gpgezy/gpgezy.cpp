#include "gpgezy.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include "actionsfactory.h"
#include "abstractcommandlineaction.h"
#include "constants.h"
#include "environment.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <algorithm>
#include <memory>

Gpgezy::Gpgezy(QObject *parent) :
    QObject(parent), factory_( new ActionsFactory() )
{
    createWorkingEnvirnment();
}

void Gpgezy::showUsage()
{

}

void Gpgezy::start()
{
    QStringList args = qApp->arguments();

    if (args.length() > 1) {
        // ignore app executable
        QStringList::iterator current = ++ args.begin();

        while (current != args.end()) {

            if (current->startsWith(constants::commandToken)) {
                std::auto_ptr<AbstractCommandLineAction> action(factory_->createAction(*current));

                if (action.get() != NULL) {
                    QStringList actionArgs;
                    // first arg is command name
                    std::copy(current, args.end(), std::back_inserter(actionArgs));
                    finishWork(action->execute(actionArgs));
                } else {
                    qDebug() << tr("Unrecognized command");
                    finishWork(EXIT_CODE_UNRECOGNIZED_COMMAND);
                }
            }

            ++ current;
        }
    } else {
        showUsage();
        finishWork(EXIT_CODE_CMD_LINE_IS_EMPTY);
    }
}

void Gpgezy::finishWork(int exitCode)
{
    exit(exitCode);
}

void Gpgezy::createWorkingEnvirnment()
{
    QString dataDir = Environment::getDataDirectory();

    if (!dataDir.isEmpty()) {
        QDir dir(dataDir);

        if (!dir.exists(dataDir)) {

            if (!dir.mkdir(dataDir)) {

                qWarning() << tr("can't create data directory");
                finishWork(EXIT_CODE_DATA_DIR_IS_EMPTY);
            }
        }
    } else {
        qWarning() << tr("data directory is empty!");
        finishWork(EXIT_CODE_DATA_DIR_IS_EMPTY);
    }

    QString dbFilePath = Environment::getDatabaseFilePath();

    if (!dbFilePath.isEmpty()) {
        QSqlDatabase db = QSqlDatabase::addDatabase(constants::databaseDriver, constants::dbConnectionName);

        if (db.isValid()) {
            db.setDatabaseName(dbFilePath);

            if (db.open())
                createTables(db);
            else {
                qWarning() << tr("can't open database");
                finishWork(EXIT_CODEC_DB_OPENING_FAILED);
            }
        } else {
            qWarning() << tr("could not load database driver");
            finishWork(EXIT_CODE_DB_DRIVER_IS_NOT_LOADED);
        }
    } else {
        qWarning() << tr("data base file path is empty");
        finishWork(EXIT_CODE_DB_FILE_PATH_IS_EMPTY);
    }
}

void Gpgezy::createTables(QSqlDatabase &db)
{
    QFile file(":/files/keys_table.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QSqlQuery query(db);
    query.exec(file.readAll());
}

void Gpgezy::showWarningAndFinish(const QString& warning, int exitCode)
{
    qWarning() << warning;
    finishWork(exitCode);
}
