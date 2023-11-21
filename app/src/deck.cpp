#include "lib/deck.h"

#include <QRandomGenerator>

Deck::Deck(const QString &name, Privacy privacy, unsigned int numOfCardsPerTest, const QImage &thumbnail)
    : m_deckId(QRandomGenerator::global()->generate()),
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(thumbnail),
    m_rating(),
    m_numOfCardsPerTest(numOfCardsPerTest)
{}

Deck::Deck(const QString &name, Privacy privacy, unsigned int numOfCardsPerTest)
    : m_deckId(QRandomGenerator::global()->generate()),
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(),
    m_rating(),
    m_numOfCardsPerTest(numOfCardsPerTest)
{}


void Deck::addCard(Card card)
{
    m_cards.append(card);
}

void Deck::updateRating(unsigned int grade)
{
    m_rating.addNewRating(grade);
}
