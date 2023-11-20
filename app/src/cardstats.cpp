#include "lib/cardstats.h"

#include <QVector>

CardStats::CardStats()
    :m_grades()
    ,m_timesAnswered(0)
    ,m_average(0)
{}

CardStats::~CardStats()
{}

void CardStats::addNewGrade(unsigned grade){
    m_grades.append(grade);
    m_timesAnswered++;

    // or calculate it again
    m_average = (m_average * (m_timesAnswered-1) + grade) / m_timesAnswered;
}

