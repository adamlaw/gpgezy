#include "gpgezy.h"
#include <QCoreApplication>
#include <QStringList>
#include <QFileInfo>
#include "actionsfactory.h"
#include "abstractcommandlineaction.h"
#include "constants.h"
#include "environment.h"
#include <QSqlDatabase>
#include <QDebug>

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
        QStringList::const_iterator current = ++ args.begin();

        while (current != args.end()) {

            if (current->startsWith(constants::commandToken)) {
                AbstractCommandLineAction* action = factory_->createAction(*current, this);

                if (action != NULL) {
                    connect(action, SIGNAL(finished(int)), this, SLOT(finishWork(int)));
                    finishWork(action->execute(args));
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
        QSqlDatabase db = QSqlDatabase::addDatabase(constants::databaseDriver);

        if (db.isValid()) {

        } else {
            qWarning() << tr("could not load database driver");
            finishWork(EXIT_CODE_DB_DRIVER_IS_NOT_LOADED);
        }
    } else {
        qWarning() << tr("data directory is empty!");
        finishWork(EXIT_CODE_DATA_DIR_IS_EMPTY);
    }
}

void Gpgezy::showWarningAndFinish(const QString& warning, int exitCode)
{
    qWarning() << warning;
    finishWork(exitCode);
}
