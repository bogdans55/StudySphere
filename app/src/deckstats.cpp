#include "lib/deckstats.h"

DeckStats::DeckStats() : m_user(), m_deck(), m_grades(), m_timesUsed(0u), m_creationDate(QDate::currentDate()) {}

DeckStats::DeckStats(User user, Deck deck, QVector<unsigned int> grades, unsigned timesUsed, QDate creationDate)
    : m_user(user)
    , m_deck(deck)
    , m_grades(grades)
    , m_timesUsed(timesUsed)
    , m_creationDate(creationDate)
{}

DeckStats::DeckStats(User user, Deck deck)
    : m_user(user)
    , m_deck(deck)
    , m_grades(deck.cards().length())
    , m_timesUsed(0u)
    , m_creationDate(QDate::currentDate())
{}

DeckStats::DeckStats(const DeckStats &deckStats)
    : m_user(deckStats.m_user)
    , m_deck(deckStats.m_deck)
    , m_grades(deckStats.m_grades)
    , m_timesUsed(deckStats.m_timesUsed)
    , m_creationDate(deckStats.m_creationDate)
{}

void DeckStats::addGrade(unsigned int cardIndex, unsigned int grade)
{
    m_grades[cardIndex] = grade;
}

void DeckStats::usedDeck()
{
    m_timesUsed++;
}

QVariant DeckStats::toVariant() const
{
    QVariantMap map;
    map.insert("User", m_user.toVariant());
    map.insert("TimesUsed", m_timesUsed);
    map.insert("CreationDate", m_creationDate);
    map.insert("Deck", m_deck.toVariant());

    QVariantList grades;
    for(unsigned value : m_grades)
        grades.append(value);
    map.insert("Grades", grades);

    return map;
}

void DeckStats::fromVariant(const QVariant& variant)
{
    QVariantMap map = variant.toMap();

    m_user.fromVariant(map.value("User"));
    m_timesUsed = map.value("TimesUsed").toInt();
    m_creationDate = map.value("CreationDate").toDate();
    m_deck.fromVariant(map.value("Deck"));

    m_grades.clear();
    QVariantList gradesList = map.value("Grades").toList();
    for (const QVariant& grade : gradesList) {
        m_grades.append(grade.toInt());
    }
}
