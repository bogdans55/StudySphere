#include "lib/studysession.h"

#include <algorithm>
#include <random>
#include <numeric>
#include <QDebug>

StudySession::StudySession(const User &user, const Deck &deck)
    : m_user(user),
    m_deck(deck)
{}

void StudySession::startSession()
{
    m_timeStarted = time(NULL);
}

void StudySession::endSession()
{
    m_timeEnded = time(NULL);
}
QVector<unsigned> StudySession::chooseCardSequence(Deck &deck, unsigned num_cards)
{
    QVector<unsigned> selectedCards(num_cards);
    QVector<unsigned> cardIndices(num_cards);
    std::iota(cardIndices.begin(), cardIndices.end(), 0);
    std::sample(cardIndices.begin(), cardIndices.end(), std::back_inserter(selectedCards), num_cards, std::mt19937 {std::random_device{}()});
    m_currentCardIndex = 0;
    return selectedCards;
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
