#ifndef CARDSTATS_H
#define CARDSTATS_H

#include <QVector>

class CardStats
{
public:
    CardStats();
    ~CardStats();

    void addNewGrade(unsigned grade);

    // Getters
    inline QVector<unsigned> grades() const { return m_grades; }
    inline unsigned timesAnswered() const { return m_timesAnswered; }
    inline double average() const { return m_average; }

private:
    QVector<unsigned> m_grades;
    unsigned m_timesAnswered;
    double m_average;
};

#endif // CARDSTATS_H
