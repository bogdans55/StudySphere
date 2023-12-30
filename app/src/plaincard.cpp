#include "lib/plaincard.h"
#include "lib/card.h"

PlainCard::PlainCard() : Card() {}

PlainCard::PlainCard(QString questionText, QString answerText, Difficulty questionDifficulty)
	: Card(questionText, answerText, questionDifficulty)
{}

PlainCard::~PlainCard() {}
