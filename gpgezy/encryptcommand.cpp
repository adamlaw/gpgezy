#include "encryptcommand.h"
#include "constants.h"
#include <QFileInfo>
#include <QStringList>
#include <QtCrypto>
#include <QDebug>

EncryptCommand::EncryptCommand()
{}

int EncryptCommand::execute(const QStringList& args)
{
    if (args.size() > 2) {
        QStringList files;
        QString key;
        QStringList::const_iterator iter = ++ args.begin();

        while (iter != args.end()) {

            if (iter->startsWith(constants::commandToken)) {
                QString str = QString(constants::commandToken) + "key";

                if (*iter == str) {
                    ++ iter;

                    if (iter != args.end()) {
                        if (QFileInfo(*iter).exists())
                            key = *iter;
                        else
                            keyFileById("sdsds");
                    } else
                        break;
                }
            }

            else {
                if (QFileInfo(*iter).exists())
                    files << *iter;
                else {
                    qDebug() << "File '" << *iter << "' doesn't exists";
                    return EXIT_CODE_INVALID_ARGUMENT;
                }
            }

            ++ iter;
        }
    } else {
        qDebug() << "You should enter at least 2 args. Try --help";
        return EXIT_CODE_INVALID_ARGUMENT;
    }



    return EXIT_CODE_SUCCESS;
}
