#ifndef DECKSTATS_H
#define DECKSTATS_H

#include <QDate>
#include <QMap>
#include "lib/user.h"
#include "lib/card.h"

class DeckStats
{
  private:
    User m_user;
    QMap <Card, unsigned> m_grades;
    unsigned m_timesUsed;
	QDate m_creationDate;

  public:
    DeckStats();
    DeckStats(User user, QMap <Card, unsigned> grades, unsigned timesUsed, QDate creationDate);
	~DeckStats() {}

    inline User user() const {return m_user;}

    inline QMap <Card, unsigned> grades() {return m_grades;}

	inline unsigned int timesUsed() const { return m_timesUsed; }

	inline QDate creationDate() const { return m_creationDate; }

    void addGrade(Card& card, unsigned grade);

	//    TODO
	//    void calculate();
	//    void update();
};

#endif // DECKSTATS_H
