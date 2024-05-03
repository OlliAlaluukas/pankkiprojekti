QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    environment.cpp \
    htiedot.cpp \
    kuitti.cpp \
    main.cpp \
    mainwindow.cpp \
    nosto.cpp \
    nostomuusumma.cpp \
    otarahatkuitti.cpp \
    saldo.cpp \
    tilisiirto.cpp \
    tilitapahtumat.cpp \
    timemaster.cpp \
    valitse.cpp \
    valitsetili.cpp
HEADERS += \
    htiedot.h \
    kuitti.h \
    mainwindow.h \
    nosto.h \
    nostomuusumma.h \
    otarahatkuitti.h \
    saldo.h \
    tilisiirto.h \
    tilitapahtumat.h \
    timemaster.h \
    valitse.h \
    environment.h \
    valitsetili.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





win32: LIBS += -L$$PWD/../Pindll/build/debug/ -lPindll

INCLUDEPATH += $$PWD/../Pindll
DEPENDPATH += $$PWD/../Pindll

win32: LIBS += -L$$PWD/../SerialReaderdll/build/debug/ -lSerialReaderdll

INCLUDEPATH += $$PWD/../SerialReaderdll
DEPENDPATH += $$PWD/../SerialReaderdll

FORMS += \
    htiedot.ui \
    kuitti.ui \
    mainwindow.ui \
    nosto.ui \
    nostomuusumma.ui \
    otarahatkuitti.ui \
    saldo.ui \
    tilisiirto.ui \
    tilitapahtumat.ui \
    valitse.ui \
    valitsetili.ui

DISTFILES +=
