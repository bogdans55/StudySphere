cmake_minimum_required(VERSION 3.12)
project(myserver_tests)

find_package(Qt6 COMPONENTS Core Network REQUIRED)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(Catch2)

# add_executable(tests test_myserver.cpp)

# add_executable(tests ${TEST_SOURCES} ${CPP_SOURCES} catch.hpp)
add_executable(tests
    ../myServer.cpp
    ../myServer.h
    ../Privacy.h
    ../main.cpp
    test_myserver.cpp
    catch.hpp
)
target_link_libraries(tests Qt6::Core Qt6::Network Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ../)  # Assuming MyServer.h is in ../src
