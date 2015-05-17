#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <QtGlobal>
#include <QMessageLogContext>
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QWidget>

class QMessageLogContext;
class QString;
class QDateTime;
class QFile;
class QTextStream;
class QIODevice;

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    QString dt = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
    QString txt = QString("[%1] ").arg(dt);

    switch (type)
    {
        case QtDebugMsg: {
            txt += QString("{Debug} \t\t %1").arg(msg);
            break;
        }
        case QtWarningMsg: {
            txt += QString("{Warning} \t %1").arg(msg);
            break;
        }
        case QtCriticalMsg: {
            txt += QString("{Critical} \t %1").arg(msg);
            break;
        }
        case QtFatalMsg: {
            txt += QString("{Fatal} \t\t %1").arg(msg);
            abort();
        }
        default: {
            break;
        }
     }

     QFile outFile("LogFile.log");
     outFile.open(QIODevice::WriteOnly | QIODevice::Append);

     QTextStream textStream(&outFile);
     textStream << txt << endl;
}

#endif
