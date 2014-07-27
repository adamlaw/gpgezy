#include "encryptcommand.h"
#include "constants.h"
#include <QFileInfo>
#include <QStringList>
#include <QDebug>
#include "pgpprocess.h"
#include "pgpkey.h"

EncryptCommand::EncryptCommand()
{}

int EncryptCommand::execute(const QStringList& args)
{
    if (args.size() > 2) {
        QStringList files;
        QString key_file;
        QStringList::const_iterator iter = ++ args.begin();

        while (iter != args.end()) {

            if (iter->startsWith(constants::commandToken)) {
                QString str = QString(constants::commandToken) + "keyname";

                if (*iter == str) {
                    ++ iter;

                    if (iter != args.end()) {

                        if (QFileInfo(*iter).exists())
                            key_file = *iter;

                    } else
                        break;
                }

                else if (*iter == QString(constants::commandToken) + "keyid") {
                    ++ iter;

                    if (iter != args.end()) {
                        // TODO
                        qDebug() << keysById(*iter);
                    }

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

        if (!key_file.isEmpty()) {

            if (!files.isEmpty()) {

                for (QStringList::const_iterator current = files.begin(); current != files.end(); ++ current) {

                    PGPKey key(key_file);
                    PGPProcess process;

                    if (key.isPublic())
                        process.encryptFile(*current, key, PGPKey());
                    else
                        process.encryptFile(*current, PGPKey(), key);
                }
            } else
                qDebug() << "You should provide at least one file, please try --help";
        } else
            qDebug() << "You should provide key, please try --help";

    } else {
        qDebug() << "You should enter at least 2 args. Try --help";
        return EXIT_CODE_INVALID_ARGUMENT;
    }



    return EXIT_CODE_SUCCESS;
}
