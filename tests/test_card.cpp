#include "catch.hpp"
#include "../app/lib/card.h"

TEST_CASE("Card Constructors", "[Card]") {
	SECTION("Default Constructor") {
		Card card;
		REQUIRE(card.questionText().isEmpty());
		REQUIRE(card.questionAnswer().isEmpty());
		REQUIRE(card.questionDifficulty() == Difficulty::EASY);
	}

	SECTION("Parameterized Constructor") {
		Card card("What is the capital of France?", "Paris", Difficulty::MEDIUM);
		REQUIRE(card.questionText() == "What is the capital of France?");
		REQUIRE(card.questionAnswer() == "Paris");
		REQUIRE(card.questionDifficulty() == Difficulty::MEDIUM);
	}

	SECTION("Copy Constructor") {
		Card original("Question", "Answer", Difficulty::HARD);
		Card copy(original);
		REQUIRE(copy.questionText() == "Question");
		REQUIRE(copy.questionAnswer() == "Answer");
		REQUIRE(copy.questionDifficulty() == Difficulty::HARD);
	}
}

TEST_CASE("Card Getters", "[Card]") {
	SECTION("Question Text Getter") {
		Card card("What is the capital of Germany?", "Berlin", Difficulty::MEDIUM);
		REQUIRE(card.questionText() == "What is the capital of Germany?");
	}

	SECTION("Question Answer Getter") {
		Card card("Question", "Answer", Difficulty::HARD);
		REQUIRE(card.questionAnswer() == "Answer");
	}

	SECTION("Question Difficulty Getter") {
		Card card("Question", "Answer", Difficulty::EASY);
		REQUIRE(card.questionDifficulty() == Difficulty::EASY);
	}
}
