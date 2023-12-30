#ifndef CARD_H
#define CARD_H

#include "lib/serializable.h"
#include <QJsonObject>

enum Difficulty
{
	EASY = 0,
	MEDIUM,
	HARD
};

class Card : public Serializable
{
  public:
	Card();
	Card(QString m_questionText, QString m_answerText, Difficulty m_questionDifficulty);
	Card(const Card &card);

	~Card();

	inline QString questionText() const { return m_questionText; }

	inline QString questionAnswer() const { return m_answerText; }

	inline Difficulty questionDifficulty() const { return m_questionDifficulty; }

    void setAnswerShowed(bool answerShowed);

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

  protected:
    QString m_questionText;
    QString m_answerText;
	Difficulty m_questionDifficulty;
};

#endif // CARD_H
