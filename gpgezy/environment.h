#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QString>

class Environment
{
public:    
    static bool get(const QString& variable, QString& result);
    static QString getDataDirectory();
    static QString getDatabaseFilePath();
};

#endif // ENVIRONMENT_H
