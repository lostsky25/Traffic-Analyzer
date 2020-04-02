QT       += core gui
INCLUDEPATH += C:/WpdPack/Include
INCLUDEPATH += C:/tcpdump-4.9.3

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += WPCAP
DEFINES += HAVE_REMOTE

LIBS += -LC:/WpdPack/Lib
LIBS += -lwpcap

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CaptureInterfaces/captureinterfaces.cpp \
    CaptureInterfaces/input.cpp \
    CaptureInterfaces/options.cpp \
    CaptureInterfaces/output.cpp \
    filterexpression.cpp \
    main.cpp \
    packetlistveiw.cpp \
    payload.cpp \
    sniffpackets.cpp \
    toppanel.cpp \
    trafficanalyzerwindow.cpp

HEADERS += \
    CaptureInterfaces/captureinterfaces.h \
    CaptureInterfaces/input.h \
    CaptureInterfaces/options.h \
    CaptureInterfaces/output.h \
    filterexpression.h \
    packetlistveiw.h \
    payload.h \
    sniffpackets.h \
    toppanel.h \
    trafficanalyzerwindow.h

FORMS += \
    trafficanalyzerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
