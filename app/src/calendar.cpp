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

QVariant Calendar::toVariant() const{
    QVariantMap result;
    for (const auto& date : m_events.keys()){
        for (const auto& event : m_events[date]) {;
            result.insert("date", date);
            result.insert("time", event.first);
            result.insert("eventText", event.second);
        }
    }
    return result;
}

void Calendar::fromVariant(const QVariant& variant){
    QVariantMap map = variant.toMap();

    for (const QString& dateString : map.keys()){
        QDate date = QDate::fromString(dateString, "dd-MM-yyyy");
        QString eventText= map.value("eventText").toString();
        QTime time = QTime::fromString(map.value("time").toString(), "hh:mm");
        QPair<QTime, QString> pair (time, eventText);
        m_events[date].push_back(pair);
    }
}
