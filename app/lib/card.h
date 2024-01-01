#ifndef CARD_H
#define CARD_H

#include "serializable.h"
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
	Card(QString mQuestionText, QString mAnswerText, Difficulty mQuestionDifficulty);
	Card(const Card &card);

	~Card() override;

	inline QString questionText() const { return m_questionText; }

	inline QString questionAnswer() const { return m_answerText; }

	inline Difficulty questionDifficulty() const { return m_questionDifficulty; }

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

  protected:
    QString m_questionText;
    QString m_answerText;
	Difficulty m_questionDifficulty;
};

#endif // CARD_H
