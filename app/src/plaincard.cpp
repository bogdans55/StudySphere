#include "lib/plaincard.h"
#include "lib/card.h"

PlainCard::PlainCard() : Card() {}

PlainCard::PlainCard(QString questionText, QString answerText, Difficulty questionDifficulty)
    : Card(questionText, answerText, questionDifficulty)
{}

PlainCard::~PlainCard()
{}

//void PlainCard::flipCard()
//{
//    Card::flipCard(); // base
//}

//void PlainCard::evaluateAnswer(unsigned evaluation)
//{
//    Card::evaluateAnswer(evaluation); // base
//}
