cmake_minimum_required(VERSION 3.14)

project(Test LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

set(TEST_SOURCE_FILES
    main.cpp
    catch.hpp
    test_activity.cpp
    test_card.cpp
    test_deck.cpp
    test_deckstats.cpp
    test_user.cpp
    ../app/src/calendar.cpp
    ../app/src/planner.cpp
    ../app/src/activity.cpp
    ../app/src/card.cpp
    ../app/src/deck.cpp
    ../app/src/deckstats.cpp
    ../app/src/imagecard.cpp
    ../app/src/jsonserializer.cpp
    ../app/src/plaincard.cpp
    ../app/src/todolist.cpp
    ../app/src/user.cpp
    ../app/src/settings.cpp
)

add_executable(Test ${TEST_SOURCE_FILES})

target_link_libraries(Test PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)

include(GNUInstallDirs)
install(TARGETS Test
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
