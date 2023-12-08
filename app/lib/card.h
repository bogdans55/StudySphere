#ifndef CARD_H
#define CARD_H

#include "lib/grading.h"
#include <QJsonObject>
#include"lib/serializable.h"

// in .h .cpp ?
enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

class Card : public Serializable
{
public:
    Card();
    Card(QString m_questionText, QString m_answerText, Difficulty m_questionDifficulty);
    ~Card();
    void flipCard();
    void evaluateAnswer(unsigned evaluation);

    // Getters
    inline QString questionText() const {return m_questionText;}
    inline QString questionAnswer() const {return m_answerText;}
    inline bool answerShowed() const {return m_answerShowed;}
    inline Difficulty questionDifficulty() const {return m_questionDifficulty;}
    inline Grading stats() const {return m_stats;}

    // Setters
    void setAnswerShowed(bool answerShowed);     // public?

    void fromJson(const QJsonObject& json);
    QJsonObject toJson() const;

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

protected:
    QString m_questionText;     // was CardContent
    QString m_answerText;       // was CardContent
    bool m_answerShowed;
    Difficulty m_questionDifficulty;
    Grading m_stats;            // was CardStats

};


#endif // CARD_H
