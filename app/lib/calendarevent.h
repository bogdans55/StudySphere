#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H

#include <QString>
#include <QDateTime>
#include "lib/serializable.h"

class CalendarEvent : Serializable
{
public:
    CalendarEvent();
    CalendarEvent(QString m_eventText, QDateTime m_dateTime);
    ~CalendarEvent();

    //Getters

    inline QString eventText() const {return m_eventText;}
    inline QDateTime dateTime() {return m_dateTime;}

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

private:
    QString m_eventText;
    QDateTime m_dateTime;
};


#endif // CALENDAREVENT_H
