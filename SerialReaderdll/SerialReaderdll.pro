QT -= gui

TEMPLATE = lib
DEFINES += SERIALREADERDLL_LIBRARY

CONFIG += c++17
QT += serialport

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    serialreaderdll.cpp

HEADERS += \
    SerialReaderdll_global.h \
    serialreaderdll.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
