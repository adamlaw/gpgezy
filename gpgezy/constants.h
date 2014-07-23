#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace constants {

const QString commandToken = "--";
const QString databaseDriver = "QSQLITE";

}

#define EXIT_CODE_DATA_DIR_IS_EMPTY       1
#define EXIT_CODE_DB_DRIVER_IS_NOT_LOADED 2
#define EXIT_CODE_CMD_LINE_IS_EMPTY       3
#define EXIT_CODE_UNRECOGNIZED_COMMAND    4

#endif // CONSTANTS_H
