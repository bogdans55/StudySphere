#include "lib/deckstats.h"

#include <QDate>

DeckStats::DeckStats() : m_user(), m_grades(), m_timesUsed(0u), m_creationDate(QDate::currentDate()) {}

DeckStats::DeckStats(User user, QMap <Card, unsigned> grades, unsigned timesUsed, QDate creationDate)
    : m_user(user)
    , m_grades(grades)
    , m_timesUsed(timesUsed)
    , m_creationDate(creationDate)
{}


void DeckStats::addGrade(Card &card, unsigned int grade)
{
    m_grades.insert(card, grade);
}
