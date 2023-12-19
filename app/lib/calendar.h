#ifndef CALENDAR_H
#define CALENDAR_H

#include "lib/calendarevent.h"
#include <QMap>
#include "lib/serializable.h"
#include <QDate>
#include <QPair>
#include <QTime>

class Calendar : public Serializable
{
private:
    QMap<QDate, QPair<QTime, QString>> m_events;
public:
    Calendar();
    ~Calendar();


    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

    void addEvent(QDate date, QTime time, QString text);

    inline QMap<QDate,  QPair<QTime, QString>> events() const {return m_events;}
};


#endif // CALENDAR_H
