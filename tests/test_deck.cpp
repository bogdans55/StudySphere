#include <catch.hpp>
#include "../app/lib/deck.h"

TEST_CASE("Deck Constructors", "[Deck]") {
    SECTION("Default Constructor") {
        Deck deck;
        REQUIRE(deck.deckId() == 0);
        REQUIRE(deck.name().isEmpty());
        REQUIRE(deck.privacy() == Privacy::PRIVATE);
        REQUIRE(deck.cards().isEmpty());
    }

    SECTION("Parameterized Constructor") {
        User user("John Doe");
        Deck deck("Math Deck", user, Privacy::PRIVATE);
        REQUIRE(deck.deckId() == 0);
        REQUIRE(deck.name() == "Math Deck");
        REQUIRE(deck.privacy() == Privacy::PRIVATE);
        REQUIRE(deck.cards().isEmpty());
    }

}

TEST_CASE("Deck Methods", "[Deck]") {
    SECTION("Add Card") {
        Deck deck;
        Card* card = new Card("Pitanje", "Odgovor", Difficulty::EASY);
        deck.addCard(card);
        REQUIRE(deck.cards().size() == 1);
        REQUIRE(deck.cards().first() == card);
    }

}

TEST_CASE("Deck Getters", "[Deck]") {
    User user("John Doe");

    SECTION("Deck Id Getter") {
        Deck deck;
        deck.setId(42);
        REQUIRE(deck.deckId() == 42);
    }

    SECTION("Name Getter") {
        Deck deck("Math Deck", user, Privacy::PRIVATE);
        REQUIRE(deck.name() == "Math Deck");
    }

    SECTION("Cards Getter") {
        Deck deck;
        Card* card1 = new Card("Pitanje1", "Odgovor1", Difficulty::EASY);
        Card* card2 = new Card("Pitanje2", "Odgovor2", Difficulty::EASY);
        deck.addCard(card1);
        deck.addCard(card2);
        QVector<Card*> cards = deck.cards();
        REQUIRE(cards.size() == 2);
        REQUIRE(cards.contains(card1));
        REQUIRE(cards.contains(card2));
    }

    SECTION("Privacy Getter") {
        Deck deck("Science Deck", user, Privacy::PUBLIC);
        REQUIRE(deck.privacy() == Privacy::PUBLIC);
    }

    SECTION("User Getter") {
        Deck deck("History Deck", user, Privacy::PRIVATE);
        REQUIRE(deck.user().username() == user.username());
    }
}
