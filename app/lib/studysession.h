#ifndef STUDYSESSION_H
#define STUDYSESSION_H

#include <QString>
#include <QVector>
#include <iostream>
#include <time.h>

#include "card.h"
#include "deck.h"
#include "deckstats.h"
#include "user.h"

class StudySession
{
  private:
	User m_user;
	Deck *m_deck;
	time_t m_timeStarted;
	time_t m_timeEnded;
	QVector<unsigned> m_cardSequence;
	unsigned m_currentCardIndex;
	bool m_answerShowed = false;
	DeckStats *m_deckStats;

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

	inline DeckStats *deckStats() { return m_deckStats; }

	void startSession();
	void endSession();
	void chooseCardSequence(unsigned numCards);
	void nextCard();
	Card getCurrentCard();
	void flipCard();
	bool hasNextCard();
};

#endif // STUDYSESSION_H
