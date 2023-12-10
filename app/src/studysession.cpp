#include "lib/studysession.h"

#include <algorithm>
#include <random>
#include <numeric>
#include <QDebug>

StudySession::StudySession()
    : m_user(),
    m_deck()
{}

StudySession::StudySession(const User &user, const Deck &deck)
    : m_user(user),
    m_deck(deck)
{}

StudySession::StudySession(const StudySession &session)
    : m_user(session.m_user)
    , m_deck(session.m_deck)
    , m_cardSequence(session.m_cardSequence)
    , m_currentCardIndex(session.m_currentCardIndex)
    , m_timeStarted(session.m_timeStarted)
    , m_timeEnded(session.m_timeEnded)
{}

StudySession::~StudySession()
{}

void StudySession::startSession()
{
    m_timeStarted = time(NULL);
    this->chooseCardSequence(m_deck.cards().length());   // TODO     Treba napraviti prozor za biranje numCards atributa
}

void StudySession::endSession()
{
    m_timeEnded = time(NULL);
}
void StudySession::chooseCardSequence(unsigned num_cards)
{
    QVector<unsigned> selectedCards(num_cards);
    QVector<unsigned> cardIndices(num_cards);
    std::iota(cardIndices.begin(), cardIndices.end(), 0);
    std::sample(cardIndices.begin(), cardIndices.end(), std::back_inserter(selectedCards), num_cards, std::mt19937 {std::random_device{}()});
    m_currentCardIndex = 0;
    m_cardSequence = selectedCards;
}
void StudySession::nextCard()
{
    m_currentCardIndex++;
    if(m_currentCardIndex > m_cardSequence.length()) qDebug() << "Used nextCard() without anymore cards in the card sequence";
}
Card StudySession::getCurrentCard()
{
    return m_deck.cards()[m_cardSequence[m_currentCardIndex]];
}
void StudySession::saveStatus()
{
    //TODO
}
