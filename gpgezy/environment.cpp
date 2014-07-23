#include "environment.h"
#include <QDir>
#include <QCoreApplication>

#ifndef Q_OS_WIN
#include <cstdlib>
#endif

bool Environment::get(const QString& variable, QString &result)
{
#ifndef Q_OS_WIN
    char* res = getenv(variable.toLatin1().constData());

    if (res != NULL) {
        result = res;
        return true;
    }
#endif

    return false;
}

QString Environment::getDataDirectory()
{
#ifndef Q_OS_WIN
    QString home;

    if (get("HOME", home)) {
        home += QDir::separator() + '.' + qApp->applicationName();
        return home;
    }
#endif

    return QString();
}

QString Environment::getDatabaseFilePath()
{
    QString dataDir = Environment::getDataDirectory();

    if (!dataDir.isEmpty())
        return dataDir + QDir::separator() + qApp->applicationName() + ".sqlite";

    return QString();
}
