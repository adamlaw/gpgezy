#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants {

namespace {

const char* commandToken = "--";
const char* databaseDriver = "QSQLITE";
const char* dbConnectionName = "gpgezy_connection";
}
}

#define EXIT_CODE_SUCCESS                 0
#define EXIT_CODE_DATA_DIR_IS_EMPTY       1
#define EXIT_CODE_DB_DRIVER_IS_NOT_LOADED 2
#define EXIT_CODE_CMD_LINE_IS_EMPTY       3
#define EXIT_CODE_UNRECOGNIZED_COMMAND    4
#define EXIT_CODE_DB_FILE_PATH_IS_EMPTY   5
#define EXIT_CODEC_DB_OPENING_FAILED      6
#define EXIT_CODE_INVALID_ARGUMENT        7
#define EXIT_CODE_OPENPGP_IS_NOT_SUPORTED 8

#endif // CONSTANTS_H
