QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QMAKE_CXXFLAGS += -g

# TEMPLATE = subdirs

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/deckpreviewwindow.cpp \
    src/calendar.cpp \
    src/planner.cpp \
    src/scheduleitem.cpp \
    src/activity.cpp \
    src/activityitem.cpp \
    src/plannerscene.cpp \
    src/deckitem.cpp \
    src/libraryscene.cpp \
    src/logindialog.cpp \
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
    src/todolist.cpp \
    src/user.cpp \
    src/settings.cpp \
    src/mainwindow.cpp \

HEADERS += \
    lib/deckpreviewwindow.h \
    lib/activity.h \
    lib/activityitem.h \
    lib/calendar.h \
    lib/deckitem.h \
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
    lib/libraryscene.h \
    lib/plaincard.h \
    lib/planner.h \
    lib/serializable.h \
    lib/serializer.h \
    lib/studysession.h \
    lib/library.h \
    lib/studysessionwindow.h \
    lib/todolist.h \
    lib/user.h \
    lib/settings.h \
    lib/mainwindow.h \
    lib/plannerscene.h \
    lib/scheduleitem.h \
    lib/logindialog.h \

FORMS += \
    forms/deckpreviewwindow.ui \
    forms/createdeckwindow.ui \
    forms/createdeckdialog.ui \
    forms/mainwindow.ui \
    forms/studysessionwindow.ui \
    forms/logindialog.ui

RESOURCES += \
    res/icons.qrc \
    res/themes.qrc \
    res/translations.qrc

# SUBDIRS += \
#     src/main \
#     tests


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
