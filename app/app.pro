QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/cardstats.cpp \
    src/createdeckwindow.cpp \
    src/createdeckdialog.cpp \
    src/browser.cpp \
    src/card.cpp \
    src/deck.cpp \
    src/deckstats.cpp \
    src/deckrating.cpp \
    src/grading.cpp \
    src/imagecard.cpp \
    src/jsonserializer.cpp \
    src/library.cpp \
    src/main.cpp \
    src/plaincard.cpp \
    src/studysession.cpp \
    src/studysessionwindow.cpp \
    src/user.cpp \
    src/settings.cpp \
    src/mainwindow.cpp

HEADERS += \
    lib/createdeckwindow.h \
    lib/createdeckdialog.h \
    lib/browser.h \
    lib/card.h \
    lib/cardstats.h \
    lib/deck.h \
    lib/deckstats.h \
    lib/deckrating.h \
    lib/grading.h \
    lib/imagecard.h \
    lib/jsonserializer.h \
    lib/plaincard.h \
    lib/serializable.h \
    lib/serializer.h \
    lib/studysession.h \
    lib/library.h \
    lib/studysessionwindow.h \
    lib/user.h \
    lib/settings.h \
    lib/mainwindow.h

FORMS += \
    forms/createdeckwindow.ui \
    forms/createdeckdialog.ui \
    forms/mainwindow.ui \
    forms/studysessionwindow.ui

RESOURCES += \
    res/icons.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
