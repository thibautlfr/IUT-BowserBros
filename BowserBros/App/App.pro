QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bowser.cpp \
    entity.cpp \
    element.cpp \
    fireball.cpp \
    gameform.cpp \
    main.cpp \
    mario.cpp \
    menuform.cpp \
    widget.cpp

HEADERS += \
    bowser.h \
    entity.h \
    element.h \
    fireball.h \
    gameform.h \
    mario.h \
    menuform.h \
    widget.h

FORMS += \
    gameform.ui \
    menuform.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
