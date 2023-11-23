QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/createdeckwindow.cpp \
    src/createdeckdialog.cpp \
    src/card.cpp \
    src/cardcontent.cpp \
    src/cardstats.cpp \
    src/deck.cpp \
    src/deckstats.cpp \
    src/deckrating.cpp \
    src/main.cpp \
    src/user.cpp \
    src/settings.cpp \
    src/mainwindow.cpp

HEADERS += \
    lib/createdeckwindow.h \
    lib/createdeckdialog.h \
    lib/card.h \
    lib/cardcontent.h \
    lib/cardstats.h \
    lib/deck.h \
    lib/deckstats.h \
    lib/deckrating.h \
    lib/user.h \
    lib/settings.h \
    lib/mainwindow.h

FORMS += \
    forms/createdeckwindow.ui \
    forms/createdeckdialog.ui \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
