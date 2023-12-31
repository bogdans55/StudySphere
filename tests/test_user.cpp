#include <catch.hpp>
#include "../app/lib/user.h"

TEST_CASE("User Constructors and Destructor", "[User]") {
    SECTION("Parameterized Constructor") {
        User user("John");
        REQUIRE(user.username() == "John");
    }

    SECTION("Default Constructor") {
        User user;
        REQUIRE(user.username().isEmpty());
    }
}

TEST_CASE("User setUsername Method", "[User]") {
    User user;

    SECTION("Set Username") {
        user.setUsername("John");
        REQUIRE(user.username() == "John");
    }
}

TEST_CASE("Getter", "[User]")
{
    SECTION("Getter") {
        User user("John");
        REQUIRE(user.username() == "John");
    }
}
