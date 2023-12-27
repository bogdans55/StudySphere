#include "lib/studysession.h"

#include <QDebug>
#include <QRandomGenerator>
#include <algorithm>
#include <numeric>
#include <random>

StudySession::StudySession() : m_user(), m_deck() {}

StudySession::StudySession(const User &user, Deck *deck) : m_user(user), m_deck(deck) {}

StudySession::StudySession(const StudySession &session)
	: m_user(session.m_user), m_deck(session.m_deck), m_cardSequence(session.m_cardSequence),
      m_currentCardIndex(session.m_currentCardIndex), m_timeStarted(session.m_timeStarted),
    m_timeEnded(session.m_timeEnded), m_answerShowed(session.m_answerShowed)
{}

StudySession::~StudySession() {}

void StudySession::startSession()
{
	m_timeStarted = time(NULL);

    // TODO     Dovlacenje DeckStatsa
    m_deckStats = new DeckStats(m_user, *m_deck);   // TODO     Ovo izbrisati nakon sto se odradi dovlacenje

    this->chooseCardSequence(m_deck->cards().length());     // TODO     Treba napraviti prozor za biranje numCards atributa

}

void StudySession::endSession()
{
	m_timeEnded = time(NULL);
}

void StudySession::chooseCardSequence(unsigned numCards)
{
    QVector<unsigned> cardIndices(numCards);
    QVector<bool> visited(numCards);
    for (unsigned i = 0;i < numCards;i++){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::vector<double> probabilities = {0.4, 0.3, 0.2, 0.1};
        std::discrete_distribution<> distribution(probabilities.begin(), probabilities.end());
        QVector<unsigned> cardPersonalDiffIndices;
        while(cardPersonalDiffIndices.isEmpty()){
            unsigned difficulty = distribution(gen);
            for (unsigned j = 0;j < numCards;j++)
                if(m_deckStats->grades()[j] == difficulty && !visited[j])
                    cardPersonalDiffIndices.append(j);
        }
        qDebug() << cardPersonalDiffIndices;
        unsigned selectedIndex = QRandomGenerator::global()->bounded(cardPersonalDiffIndices.size());
        visited[cardPersonalDiffIndices[selectedIndex]] = true;
        cardIndices[i] = cardPersonalDiffIndices[selectedIndex];
    }
	m_currentCardIndex = 0;
    m_cardSequence = cardIndices;
    qDebug() << m_cardSequence;
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
