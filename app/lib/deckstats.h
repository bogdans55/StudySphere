#ifndef DECKSTATS_H
#define DECKSTATS_H

#include <QDate>
#include <QMap>
#include "lib/user.h"
#include "lib/card.h"

class DeckStats : public Serializable
{
  private:
    User m_user;
    QVector <unsigned> m_grades;
    unsigned m_timesUsed;
	QDate m_creationDate;

  public:
    DeckStats();
    DeckStats(User user, QVector <unsigned> grades, unsigned timesUsed, QDate creationDate);
    DeckStats(User user, unsigned int numOfGrades);
    DeckStats(const DeckStats &deckStats);
	~DeckStats() {}

    inline User user() const {return m_user;}

    inline QVector <unsigned> grades() {return m_grades;}

	inline unsigned int timesUsed() const { return m_timesUsed; }

	inline QDate creationDate() const { return m_creationDate; }

    void addGrade(unsigned cardIndex, unsigned grade);

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;
	//    TODO
	//    void calculate();
	//    void update();
};

#endif // DECKSTATS_H
