#include <utility>

#include "../lib/plaincard.h"
#include "../lib/card.h"

PlainCard::PlainCard() : Card() {}

PlainCard::PlainCard(QString questionText, QString answerText, Difficulty questionDifficulty)
    : Card(std::move(questionText), std::move(answerText), questionDifficulty)
{}

PlainCard::~PlainCard() = default;
