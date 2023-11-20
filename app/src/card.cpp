#include "lib/card.h"
#include "lib/cardcontent.h"
#include "lib/cardstats.h"

Card::Card(CardContent question, CardContent answer, Difficulty questionDifficulty)
    :m_question(question)
    ,m_answer(answer)
    ,m_questionDifficulty(questionDifficulty)
    ,m_answerShowed(false)
    ,m_stats()
{}

Card::~Card()
{}

void Card::flipCard() {
    m_answerShowed = !m_answerShowed;
}

void Card::evaluateAnswer(unsigned evaluation) {
    m_stats.addNewGrade(evaluation);
}

// Setters
void Card::setAnswerShowed(bool answerShowed) {
    m_answerShowed = answerShowed;
}
