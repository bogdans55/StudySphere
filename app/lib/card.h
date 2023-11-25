#ifndef CARD_H
#define CARD_H

#include "lib/cardcontent.h"
#include "lib/cardstats.h"
#include <QJsonObject>

// in .h .cpp ?
enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

class Card
{
public:
    Card();
    Card(CardContent m_question, CardContent m_answer, Difficulty m_questionDifficulty);
    ~Card();
    void flipCard();
    void evaluateAnswer(unsigned evaluation);

    // Getters
    inline CardContent getQuestion() const {return m_question;}
    inline CardContent getAnswer() const {return m_answer;}
    inline bool isAnswerShowed() const {return m_answerShowed;}
    inline Difficulty getQuestionDifficulty() const {return m_questionDifficulty;}
    inline CardStats getStats() const {return m_stats;}

    // Setters
    void setAnswerShowed(bool answerShowed);     // public?

    void fromJson(const QJsonObject& json);
    QJsonObject toJson() const;

private:
    CardContent m_question;
    CardContent m_answer;
    bool m_answerShowed;
    Difficulty m_questionDifficulty;
    CardStats m_stats;
};


#endif // CARD_H
