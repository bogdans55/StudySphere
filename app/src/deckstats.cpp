#include "lib/deckstats.h"

#include <QDate>

DeckStats::DeckStats() : m_user(), m_grades(), m_timesUsed(0u), m_creationDate(QDate::currentDate()) {}

DeckStats::DeckStats(User user, QVector<unsigned int> grades, unsigned timesUsed, QDate creationDate)
    : m_user(user)
    , m_grades(grades)
    , m_timesUsed(timesUsed)
    , m_creationDate(creationDate)
{}

DeckStats::DeckStats(User user, unsigned numOfGrades)
    : m_user(user)
    , m_grades(numOfGrades)
    , m_timesUsed(0u)
    , m_creationDate(QDate::currentDate())
{}

DeckStats::DeckStats(const DeckStats &deckStats)
    : m_user(deckStats.m_user)
    , m_grades(deckStats.m_grades)
    , m_timesUsed(deckStats.m_timesUsed)
    , m_creationDate(deckStats.m_creationDate)
{}



void DeckStats::addGrade(unsigned int cardIndex, unsigned int grade)
{
    m_grades[cardIndex] = grade;
}

QVariant DeckStats::toVariant() const
{
    QVariantMap map;
    map.insert("User", user().toVariant());
    map.insert("TimesUsed", timesUsed());
    map.insert("CreationDate", creationDate());

    QVariantList grades;

    for(int value : m_grades)
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

    m_grades.clear();
    QVariantList gradesList = map.value("Grades").toList();
    for (const QVariant& grade : gradesList) {
        m_grades.append(grade.toInt());
    }
}
