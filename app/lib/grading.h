#ifndef GRADING_H
#define GRADING_H

#include <QVector>

class Grading
{
public:
    Grading();
    ~Grading();

    void addNewGrade(unsigned grade);

    // Getters
    inline QVector<unsigned> grades() const { return m_grades; }
    inline unsigned timesGraded() const { return m_timesGraded; }
    inline double average() const { return m_average; }

protected:
    QVector<unsigned> m_grades;
    unsigned m_timesGraded;
    double m_average;
};

#endif // GRADING_H
