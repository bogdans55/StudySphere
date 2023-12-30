#include "../lib/deckstats.h"

DeckStats::DeckStats() : m_grades(), m_timesUsed(0u) {}

DeckStats::DeckStats(unsigned int numGrades)
	: m_grades(numGrades)
	, m_timesUsed(0u)
    , m_creationDate(QDate::currentDate().toString())
{}

DeckStats::DeckStats(const DeckStats &deckStats)
    : m_grades(deckStats.m_grades)
    , m_timesUsed(deckStats.m_timesUsed)
    , m_creationDate(deckStats.m_creationDate)
{}

DeckStats::~DeckStats() {}

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
    map.insert("TimesUsed", m_timesUsed);
    map.insert("CreationDate", m_creationDate);

    QVariantList grades;
    for(unsigned value : m_grades)
        grades.append(value);
    map.insert("Grades", grades);

    return map;
}

void DeckStats::fromVariant(const QVariant& variant)
{
	QVariantMap map = variant.toMap();
	QVariantMap deckStats = map.value("deckStats").toMap();

	m_timesUsed = deckStats.value("TimesUsed").toUInt();
    m_creationDate = deckStats.value("CreationDate").toString();

	m_grades.clear();
	QVariant gradesVariant = deckStats.value("Grades");
	auto gradesList = gradesVariant.toList();
	for (const QVariant& grade : gradesList) {
		m_grades.push_back(static_cast<unsigned int>(grade.toULongLong()));
	}
}
