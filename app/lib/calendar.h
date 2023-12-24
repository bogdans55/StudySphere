#ifndef CALENDAR_H
#define CALENDAR_H

#include <QMap>
#include "lib/serializable.h"
#include <QDate>
#include <QPair>
#include <QTime>

class Calendar : public Serializable
{
private:
    QMap<QDate, QVector<QPair<QTime, QString>>> m_events;
public:
    Calendar();
    ~Calendar();


    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

    void addEvent(QDate date, QTime time, QString text);

    inline QMap<QDate, QVector<QPair<QTime, QString>>> events() const {return m_events;}
};


#endif // CALENDAR_H
