#include "lib/studysession.h"

#include <QDebug>
#include <algorithm>
#include <numeric>
#include <random>

StudySession::StudySession() : m_user(), m_deck() {}

StudySession::StudySession(const User &user, Deck *deck) : m_user(user), m_deck(deck) {}

StudySession::StudySession(const StudySession &session)
	: m_user(session.m_user), m_deck(session.m_deck), m_cardSequence(session.m_cardSequence),
	  m_currentCardIndex(session.m_currentCardIndex), m_timeStarted(session.m_timeStarted),
	  m_timeEnded(session.m_timeEnded)
{}

StudySession::~StudySession() {}

void StudySession::startSession()
{
	m_timeStarted = time(NULL);
	this->chooseCardSequence(m_deck->cards().length()); // TODO     Treba napraviti prozor za biranje numCards atributa
}

void StudySession::endSession()
{
	m_timeEnded = time(NULL);
}

void StudySession::chooseCardSequence(unsigned num_cards)
{
	QVector<unsigned> cardIndices(num_cards);
	std::iota(cardIndices.begin(), cardIndices.end(), 0);
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cardIndices.begin(), cardIndices.end(), g);
	m_currentCardIndex = 0;
	m_cardSequence = cardIndices;
	for (int i = 0; i < cardIndices.length(); i++)
		qDebug() << m_deck->cards()[cardIndices[i]]->questionText() << " " << cardIndices[i];
}

void StudySession::nextCard()
{
	m_currentCardIndex++;
	m_answerShowed = false;
}

Card StudySession::getCurrentCard()
{
	return *m_deck->cards()[m_cardSequence[m_currentCardIndex]];
}

void StudySession::saveStatus()
{
	// TODO
}

void StudySession::flipCard()
{
	m_answerShowed = !m_answerShowed;
}

bool StudySession::hasNextCard()
{
	return m_currentCardIndex + 1 < m_cardSequence.length();
}
