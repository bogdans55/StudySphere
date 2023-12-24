#include "lib/calendar.h"

Calendar::Calendar()
    :m_events()
{}

Calendar::~Calendar()
{}

void Calendar::addEvent(QDate date, QTime time,  QString text){
    QPair<QTime, QString> pair (time, text);
    m_events[date].push_back(pair);
}

QVariant Calendar::toVariant() const {
	QVariantMap result;

	for (const auto& date : m_events.keys()) {
		QVariantList eventsList;

		for (const auto& event : m_events[date]) {
			QVariantMap eventMap;
			eventMap.insert("date", date);
			eventMap.insert("time", event.first);
			eventMap.insert("eventText", event.second);

			eventsList.append(eventMap);
		}

		result.insert(date.toString(), eventsList);
	}

	return result;
}
void Calendar::fromVariant(const QVariant& variant){
	QVariantMap map = variant.toMap();

	for (const auto& dateKey : map.keys()) {
		QDate date = QDate::fromString(dateKey, "ddd MMM dd yyyy");
		QVariantList eventsList = map.value(dateKey).toList();

		for (const auto& eventVariant : eventsList) {
			QVariantMap eventMap = eventVariant.toMap();

			QTime time = QTime::fromString(eventMap.value("time").toString());
			QString eventText = eventMap.value("eventText").toString();

			QPair<QTime, QString> pair(time, eventText);
			m_events[date].push_back(pair);
		}
	}
}
