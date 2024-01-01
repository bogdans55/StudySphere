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
    ../app/src/activity.cpp \
    ../app/src/card.cpp \
    ../app/src/deck.cpp \
    ../app/src/deckstats.cpp \
    ../app/src/imagecard.cpp \
    ../app/src/jsonserializer.cpp \
    ../app/src/plaincard.cpp \
    ../app/src/servercommunicator.cpp \
    ../app/src/studysession.cpp \
    ../app/src/todolist.cpp \
    ../app/src/user.cpp \
    ../app/src/settings.cpp \
    test_activity.cpp \
    test_card.cpp \
    test_deck.cpp \
    main.cpp \
    test_deckstats.cpp \
    test_user.cpp

HEADERS += \
    ../app/lib/activity.h \
    ../app/lib/calendar.h \
    ../app/lib/card.h \
    ../app/lib/deck.h \
    ../app/lib/deckstats.h \
    ../app/lib/imagecard.h \
    ../app/lib/jsonserializer.h \
    ../app/lib/plaincard.h \
    ../app/lib/planner.h \
    ../app/lib/serializable.h \
    ../app/lib/serializer.h \
    ../app/lib/servercommunicator.h \
    ../app/lib/studysession.h \
    ../app/lib/todolist.h \
    ../app/lib/user.h \
    ../app/lib/settings.h


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
