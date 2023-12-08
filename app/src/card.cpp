#include "lib/card.h"

Card::Card()
    :m_questionText()
    ,m_answerText()
    ,m_answerShowed()
    ,m_questionDifficulty()
    ,m_stats()
{}

Card::Card(QString questionText, QString answerText, Difficulty questionDifficulty)
    :m_questionText(questionText)
    ,m_answerText(answerText)
    ,m_answerShowed(false)
    ,m_questionDifficulty(questionDifficulty)
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
    m_questionText.operator =(json["question"].toString());
    m_answerText.operator =(json["answer"].toString());

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
    json["question"] = m_questionText;
    json["answer"] = m_answerText;

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

QVariant Card::toVariant() const{
    QVariantMap map;
    map.insert("question", m_questionText);
    map.insert("answer", m_answerText);
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
    map.insert("difficulty", difficultyStr);
    return map;
}

void Card::fromVariant(const QVariant &variant){
    QVariantMap map = variant.toMap();
    m_questionText = map.value("question").toString();
    m_answerText = map.value("answer").toString();
    QString questionDifficultyStr = map.value("difficulty").toString();
    if(questionDifficultyStr == "EASY"){
        m_questionDifficulty = Difficulty::EASY;
    }
    else if(questionDifficultyStr == "MEDIUM"){
        m_questionDifficulty = Difficulty::MEDIUM;
    }
    else if(questionDifficultyStr == "HARD"){
        m_questionDifficulty = Difficulty::HARD;
    }
}
