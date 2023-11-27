#include "lib/card.h"
#include "lib/cardcontent.h"
#include "lib/cardstats.h"

Card::Card()
    :m_question()
    ,m_answer()
    ,m_questionDifficulty()
    ,m_answerShowed()
    ,m_stats()
{}

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

void Card::fromJson(const QJsonObject& json){
    m_question.setText(json["question"].toString());
    m_answer.setText(json["answer"].toString());

    QString difficultyStr = json["questionDifficulty"].toString();
    if(difficultyStr == "EASY"){
        m_questionDifficulty = Difficulty::EASY;
    }
    else if(difficultyStr == "MEDIUM"){
        m_questionDifficulty = Difficulty::MEDIUM;
    }
    else if(difficultyStr == "HARD"){
        m_questionDifficulty = Difficulty::HARD;
    }
    //TODO error handling for invalid difficulty ?
}

QJsonObject Card::toJson() const{
    QJsonObject json;
    json["question"] = m_question.getText();
    json["answer"] = m_answer.getText();

    QString difficultyStr;
    switch (m_questionDifficulty) {
    case Difficulty::EASY:
        difficultyStr = "EASY";
        break;
    case Difficulty::MEDIUM:
        difficultyStr = "MEDIUM";
        break;
    case Difficulty::HARD:
        difficultyStr = "HARD";
        break;
        // Add default case or error handling for unexpected values
    }
    json["questionDifficulty"] = difficultyStr;

    return json;
}
