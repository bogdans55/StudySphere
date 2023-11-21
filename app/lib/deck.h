#ifndef DECK_H
#define DECK_H

#include <QString>
#include <QVector>
#include "card.h"
#include "lib/deckstats.h"
#include <QImage>
#include "deckrating.h"

enum class Privacy
{
    PRIVATE,
    PUBLIC
};

class Deck
{
private:
    unsigned m_deckId;
    QString m_name;
    QVector<Card> m_cards;
    Privacy m_privacy;
    DeckStats m_deckStats;
    QImage m_thumbnail;
    DeckRating m_rating;
    unsigned m_numOfCardsPerTest;

public:
    Deck(const QString &name, const QVector<Card> &cards, Privacy privacy, const DeckStats &deckStats, const QImage &thumbnail, const DeckRating &rating, unsigned int numOfCardsPerTest);
    ~Deck() {}

    inline unsigned int getDeckId() const {return m_deckId;}
    inline QString getName() const {return m_name;}
    inline QVector<Card> getCards() const {return m_cards;}
    inline Privacy getPrivacy() const {return m_privacy;}
    inline DeckStats getDeckStats() const {return m_deckStats;}
    inline QImage getThumbnail() const {return m_thumbnail;}
    inline DeckRating getRating() const {return m_rating;}
    inline unsigned int getNumOfCardsPerTest() const {return m_numOfCardsPerTest;}

    void addCard(Card card);
    void updateRating(unsigned grade);
};

#endif // DECK_H
