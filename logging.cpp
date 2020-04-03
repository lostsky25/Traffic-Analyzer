#include "logging.h"

Q_LOGGING_CATEGORY(logInfo, "Info")

Logging::Logging()
{
    logFile.reset(new QFile("../log.txt"));
    logFile.data()->open(QFile::Append | QFile::Text);
}

void Logging::messageHandler(QtMsgType type, const QString &msg){
    QTextStream outStream(logFile.data());
    outStream << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");

    switch(type){
        case QtInfoMsg:     outStream << "INF: "; break;
        case QtDebugMsg:    outStream << "DBG: "; break;
        case QtWarningMsg:  outStream << "WRN: "; break;
        case QtCriticalMsg: outStream << "CRT: "; break;
        case QtFatalMsg:    outStream << "FTL: "; break;
        default:                                  break;
    }
    outStream << " " << msg << endl;
    outStream.flush();
}
