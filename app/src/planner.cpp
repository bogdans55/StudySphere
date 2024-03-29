#include "../lib/planner.h"

Planner::Planner() : m_activities() {}

Planner::~Planner() = default;

void Planner::addActivity(Day day, Activity activity)
{
	m_activities[day].push_back(activity);
}

QString Planner::dayToString(Day day)
{
	switch (day) {
	case Day::MONDAY:
		return "Ponedeljak";
		break;
	case Day::TUESDAY:
		return "Utorak";
		break;
	case Day::WEDNESDAY:
		return "Sreda";
		break;
	case Day::THURSDAY:
		return "Četvrtak";
		break;
	case Day::FRIDAY:
		return "Petak";
		break;
	case Day::SATURDAY:
		return "Subota";
		break;
	case Day::SUNDAY:
		return "Nedelja";
		break;
	}
	return "";
}

QVariant Planner::toVariant() const
{
	QVariantMap result;
	auto keys = m_activities.keys();
	for (const auto &day : keys) {
		QVariantList activitiesList;
		for (const Activity &activity : m_activities.value(day)) {
			activitiesList.append(activity.toVariant());
		}
		result.insert(dayToString(day), activitiesList);
	}
	return result;
}

Day Planner::dayFromString(QString dayString)
{
	if (dayString == "Ponedeljak" or dayString == "Monday")
		return Day::MONDAY;
	else if (dayString == "Utorak" or dayString == "Tuesday")
		return Day::TUESDAY;
	else if (dayString == "Sreda" or dayString == "Wednesday")
		return Day::WEDNESDAY;
	else if (dayString == "Četvrtak" or dayString == "Thursday")
		return Day::THURSDAY;
	else if (dayString == "Petak" or dayString == "Friday")
		return Day::FRIDAY;
	else if (dayString == "Subota" or dayString == "Saturday")
		return Day::SATURDAY;
	else if (dayString == "Nedelja" or dayString == "Sunday")
		return Day::SUNDAY;
	else
		return Day::MONDAY;
}

void Planner::fromVariant(const QVariant &variant)
{
	QVariantMap map = variant.toMap();
	auto keys = map.keys();
	for (const QString &dayString : keys) {
		Day day = dayFromString(dayString);
		QVector<Activity> activities;
		const QVariantList activitiesList = map.value(dayString).toList();
		for (const QVariant &variant : activitiesList) {
			Activity activity;
			activity.fromVariant(variant);
			activities.append(activity);
		}
		m_activities.insert(day, activities);
	}
}

void Planner::deleteAll()
{
	m_activities.clear();
}
