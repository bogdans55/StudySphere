#ifndef STUDYSESSION_H
#define STUDYSESSION_H

#include <QString>
#include <QVector>
#include <iostream>
#include <time.h>

#include "lib/card.h"
#include "lib/deck.h"
#include "lib/user.h"

class StudySession
{
  private:
	User m_user;
	Deck *m_deck;
	unsigned m_currentCardIndex;
	time_t m_timeStarted;
	time_t m_timeEnded;
	QVector<unsigned> m_cardSequence;
	bool m_answerShowed = false;

  public:
	StudySession();
	StudySession(const User &user, Deck *deck);
	StudySession(const StudySession &session);
	~StudySession();

	inline User user() const { return m_user; }

	inline Deck *deck() { return m_deck; }

	inline unsigned currentCardIndex() const { return m_currentCardIndex; }

	inline time_t timeStarted() const { return m_timeStarted; }

	inline time_t timeEnded() const { return m_timeEnded; }

	inline QVector<unsigned> cardSequence() { return m_cardSequence; }

	inline bool answerShowed() { return m_answerShowed; }

	void startSession();
	void endSession();
	void chooseCardSequence(unsigned num_cards);
	void nextCard();
	Card getCurrentCard();
	void saveStatus();
	void flipCard();
	bool hasNextCard();
};

#endif // STUDYSESSION_H
