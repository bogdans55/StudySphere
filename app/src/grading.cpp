#include "../lib/grading.h"

#include <QVector>

Grading::Grading() : m_grades(), m_timesGraded(0), m_average(0) {}

Grading::~Grading() {}

void Grading::addNewGrade(unsigned grade)
{
	m_grades.append(grade);
	m_timesGraded++;

	// or calculate it again
	m_average = (m_average * (m_timesGraded - 1) + grade) / m_timesGraded;
}
