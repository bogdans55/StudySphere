#include "lib/deck.h"

#include <QRandomGenerator>

Deck::Deck(const QString &name, const QVector<Card> &cards, Privacy privacy, const DeckStats &deckStats, const QImage &thumbnail, const DeckRating &rating, unsigned int numOfCardsPerTest)
    : m_deckId(QRandomGenerator::global()->generate()),
    m_name(name),
    m_cards(cards),
    m_privacy(privacy),
    m_deckStats(deckStats),
    m_thumbnail(thumbnail),
    m_rating(rating),
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
