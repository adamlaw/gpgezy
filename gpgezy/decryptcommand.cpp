#include "decryptcommand.h"
#include "constants.h"
#include <QFileInfo>
#include <QDebug>

DecryptCommand::DecryptCommand()
{
}

int DecryptCommand::execute(const QStringList& args)
{
    if (args.size() > 1) {
        QStringList::const_iterator current = ++ args.begin();
        QStringList files;

        while (current != args.end()) {

            QFileInfo info(*current);

            if (info.exists()) {

                if (info.suffix() == "gpg")
                    files << *current;
                else
                    qDebug() << "Onlt *.gpg files supported";
            }
            else
                qDebug() << "File " << *current << "doesn't exist";

            ++ current;
        }

        if (!files.isEmpty()) {
        }
    }

    return EXIT_CODE_INVALID_ARGUMENT;
}
