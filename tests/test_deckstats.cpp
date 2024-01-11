#include "catch.hpp"
#include "../app/lib/deckstats.h"

TEST_CASE("DeckStats Constructors and Methods", "[DeckStats]") {
    SECTION("Default Constructor") {
        DeckStats deckStats;
        REQUIRE(deckStats.grades().isEmpty());
        REQUIRE(deckStats.timesUsed() == 0);
    }

    SECTION("Parameterized Constructor") {
        DeckStats deckStats(5);
        REQUIRE(deckStats.grades().size() == 5);
        REQUIRE(deckStats.timesUsed() == 0);
    }

    SECTION("Copy Constructor") {
        DeckStats original(3);
        original.addGrade(0, 80);
        original.addGrade(1, 90);
        original.usedDeck();

        DeckStats copy(original);
        REQUIRE(copy.grades() == original.grades());
        REQUIRE(copy.timesUsed() == original.timesUsed());
    }

}

TEST_CASE("DeckStats Methods", "[DeckStats]") {

    SECTION("Add Grade Method") {
        DeckStats deckStats(2);
        deckStats.addGrade(0, 70);
        deckStats.addGrade(1, 85);
        REQUIRE(deckStats.grades()[0] == 70);
        REQUIRE(deckStats.grades()[1] == 85);
    }

    SECTION("Used Deck Method") {
        DeckStats deckStats;
        deckStats.usedDeck();
        REQUIRE(deckStats.timesUsed() == 1);
    }

}

TEST_CASE("DeckStats Getters", "[DeckStats]") {
    SECTION("Grades Getter") {
        DeckStats deckStats(3);
        deckStats.addGrade(0, 75);
        deckStats.addGrade(1, 88);
        deckStats.addGrade(2, 92);

        QVector<unsigned> grades = deckStats.grades();
        REQUIRE(grades.size() == 3);
        REQUIRE(grades[0] == 75);
        REQUIRE(grades[1] == 88);
        REQUIRE(grades[2] == 92);
    }

    SECTION("Times Used Accessor") {
        DeckStats deckStats;
        deckStats.usedDeck();
        deckStats.usedDeck();
        REQUIRE(deckStats.timesUsed() == 2);
    }
}
