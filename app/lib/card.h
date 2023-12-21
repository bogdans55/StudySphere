#ifndef CARD_H
#define CARD_H

#include "lib/grading.h"
#include "lib/serializable.h"
#include <QJsonObject>

// in .h .cpp ?
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
	void evaluateAnswer(unsigned evaluation);

	// Getters
	inline QString questionText() const { return m_questionText; }

	inline QString questionAnswer() const { return m_answerText; }

	inline Difficulty questionDifficulty() const { return m_questionDifficulty; }

	inline Grading stats() const { return m_stats; }

	// Setters
	void setAnswerShowed(bool answerShowed); // public?

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

  protected:
	QString m_questionText; // was CardContent
	QString m_answerText;	// was CardContent
	Difficulty m_questionDifficulty;
	Grading m_stats; // was CardStats
};

#endif // CARD_H
