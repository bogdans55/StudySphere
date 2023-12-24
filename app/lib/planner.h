#ifndef PLANNER_H
#define PLANNER_H

#include "lib/activity.h"
#include "lib/serializable.h"
#include <QMap>
#include <QVector>

enum Day
{
	MONDAY = 0,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

class Planner : public Serializable
{
  private:
	QMap<Day, QVector<Activity>> m_activities;

  public:
	Planner();
	~Planner();

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

	void addActivity(Day day, Activity activity);

	static Day dayFromString(QString dayString);
	static QString dayToString(Day day);

	inline QMap<Day, QVector<Activity>> activities() const { return m_activities; }
};

#endif // PLANNER_H
