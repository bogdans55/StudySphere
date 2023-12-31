#include <catch.hpp>
#include "../app/lib/activity.h"

TEST_CASE("Activity Constructors", "[Activity]") {
    SECTION("Default Constructor") {
        Activity activity;
        REQUIRE(activity.activityText().isEmpty());
        REQUIRE(activity.start() == QTime());
        REQUIRE(activity.end() == QTime());
    }

    SECTION("Parameterized Constructor") {
        QTime startTime(9, 0);
        QTime endTime(11, 0);
        Activity activity("Meeting", startTime, endTime);

        REQUIRE(activity.activityText() == "Meeting");
        REQUIRE(activity.start() == startTime);
        REQUIRE(activity.end() == endTime);
    }
}

TEST_CASE("Activity Getters", "[Activity]") {

    QTime startTime(14, 30);
    QTime endTime(16, 0);
    Activity activity("Coding", startTime, endTime);

    SECTION("Accessor Start Time Getter") {
        REQUIRE(activity.start() == startTime);
    }

    SECTION("Accessor Start Time Getter") {
        REQUIRE(activity.end() == endTime);
    }

    SECTION("Accessor Start Time Getter") {
        REQUIRE(activity.activityText() == "Coding");
    }
}
