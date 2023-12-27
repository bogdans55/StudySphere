#ifndef DECKSTATS_H
#define DECKSTATS_H

#include <QDate>
#include <QMap>
#include "user.h"
#include "card.h"
#include "deck.h"

class DeckStats : public Serializable
{
  private:
    User m_user;
    QVector <unsigned> m_grades;
    Deck m_deck;
    unsigned m_timesUsed;
	QDate m_creationDate;

  public:
    DeckStats();
    DeckStats(User user, Deck deck, QVector <unsigned> grades, unsigned timesUsed, QDate creationDate);
    DeckStats(User user, Deck deck);
    DeckStats(const DeckStats &deckStats);
	~DeckStats() {}

    inline User user() const {return m_user;}

    inline QVector <unsigned> grades() {return m_grades;}

	inline unsigned int timesUsed() const { return m_timesUsed; }

	inline QDate creationDate() const { return m_creationDate; }

    inline Deck deck() const { return m_deck; }

    void addGrade(unsigned cardIndex, unsigned grade);
    void usedDeck();

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;
};

#endif // DECKSTATS_H
