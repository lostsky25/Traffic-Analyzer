#ifndef LOGGING_H
#define LOGGING_H

#include <QLoggingCategory>
#include <QDataStream>
#include <QDateTime>
#include <QFile>
#include <QDebug>

Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logCritical)
Q_DECLARE_LOGGING_CATEGORY(logFatal)

class Logging
{
public:
    Logging();
    ~Logging();
    void messageHandler(QtMsgType type, const QString &msg);

private:
    QScopedPointer<QFile> logFile;
};

#endif // LOGGING_H
