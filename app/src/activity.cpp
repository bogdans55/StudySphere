#include "../lib/activity.h"
#include <QVariantMap>
#include <utility>

Activity::Activity() : m_activityText(), m_start(), m_end() {}

Activity::Activity(QString activityText, QTime start, QTime end)
	: m_activityText(std::move(activityText)), m_start(start), m_end(end)
{}

Activity::~Activity() = default;

QVariant Activity::toVariant() const
{
	QVariantMap map;
	map.insert("activity", m_activityText);
	map.insert("start", m_start.toString());
	map.insert("end", m_end.toString());
	return map;
}

void Activity::fromVariant(const QVariant &variant)
{
	QVariantMap map = variant.toMap();
	m_activityText = map.value("activity").toString();
	m_start = map.value("start").toTime();
	m_end = map.value("end").toTime();
}
