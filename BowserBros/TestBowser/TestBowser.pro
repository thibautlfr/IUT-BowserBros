QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testunitbowser.cpp \
    ../App/bowser.cpp \
    ../App/entity.cpp \
    ../App/fireball.cpp

HEADERS += \
    ../App/bowser.h \
    ../App/entity.h \
    ../App/fireball.h

DISTFILES += \
    ../App/Assets/other/fireball.png \
    ../App/Assets/other/fireball.png
