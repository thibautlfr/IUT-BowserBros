QT += testlib
QT += gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testunitmario.cpp \
    ../App/entity.cpp \
    ../App/mario.cpp

HEADERS += \
    ../App/entity.h \
    ../App/mario.h
