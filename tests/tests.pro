TEMPLATE = app
QT       += core network gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

QMAKE_CXXFLAGS += -g --coverage
QMAKE_LFLAGS += --coverage

isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR=$$(CATCH_INCLUDE_DIR)
# set by Qt Creator wizard
isEmpty(CATCH_INCLUDE_DIR): CATCH_INCLUDE_DIR="./catch2"
!isEmpty(CATCH_INCLUDE_DIR): INCLUDEPATH *= $${CATCH_INCLUDE_DIR}

isEmpty(CATCH_INCLUDE_DIR): {
    message("CATCH_INCLUDE_DIR is not set, assuming Catch2 can be found automatically in your system")
}



SOURCES += \
    ../app/src/calendar.cpp \
    ../app/src/planner.cpp \
    ../app/src/scheduleitem.cpp \
    ../app/src/activity.cpp \
    ../app/src/activityitem.cpp \
    ../app/src/plannerscene.cpp \
    ../app/src/deckitem.cpp \
    # ../app/src/libraryscene.cpp \
    # ../app/src/logindialog.cpp \
    ../app/src/cardstats.cpp \
    # ../app/src/createdeckwindow.cpp \
    # ../app/src/createdeckdialog.cpp \
    ../app/src/browser.cpp \
    ../app/src/card.cpp \
    ../app/src/deck.cpp \
    ../app/src/deckstats.cpp \
    ../app/src/deckrating.cpp \
    ../app/src/grading.cpp \
    ../app/src/imagecard.cpp \
    ../app/src/jsonserializer.cpp \
    # ../app/src/deckpreviewwindow.cpp \
    ../app/src/library.cpp \
    ../app/src/plaincard.cpp \
    ../app/src/studysession.cpp \
    # ../app/src/studysessionwindow.cpp \
    ../app/src/todolist.cpp \
    ../app/src/user.cpp \
    ../app/src/settings.cpp \
    # ../app/src/mainwindow.cpp \
    test.cpp \
    main.cpp

HEADERS += \
    main.cpp \
    catch.hpp \
    ../app/lib/activity.h \
    ../app/lib/activityitem.h \
    ../app/lib/calendar.h \
    ../app/lib/deckitem.h \
    # ../app/lib/createdeckwindow.h \
    # ../app/lib/createdeckdialog.h \
    ../app/lib/browser.h \
    ../app/lib/card.h \
    ../app/lib/cardstats.h \
    ../app/lib/deck.h \
    ../app/lib/deckstats.h \
    ../app/lib/deckrating.h \
    # ../app/lib/deckpreviewwindow.h \
    ../app/lib/grading.h \
    ../app/lib/imagecard.h \
    ../app/lib/jsonserializer.h \
    # ../app/lib/libraryscene.h \
    ../app/lib/plaincard.h \
    ../app/lib/planner.h \
    ../app/lib/serializable.h \
    ../app/lib/serializer.h \
    ../app/lib/studysession.h \
    ../app/lib/library.h \
    # ../app/lib/studysessionwindow.h \
    ../app/lib/todolist.h \
    ../app/lib/user.h \
    ../app/lib/settings.h \
    # ../app/lib/mainwindow.h \
    ../app/lib/plannerscene.h \
    ../app/lib/scheduleitem.h \
    # ../app/lib/logindialog.h \

FORMS += \
../app/forms/createdeckwindow.ui \
../app/forms/createdeckdialog.ui \
../app/forms/mainwindow.ui \
../app/forms/studysessionwindow.ui \
../app/forms/logindialog.ui
../app/forms/deckpreviewwindow.ui \

RESOURCES += \
../app/res/icons.qrc \
../app/res/themes.qrc \
../app/res/translations.qrc

# TARGET = tests

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
