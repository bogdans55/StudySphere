#ifndef CALENDAR_H
#define CALENDAR_H

#include <QString>
#include <QDateTime>
#include "lib/serializable.h"

class Calendar : Serializable
{
public:
    Calendar();
    Calendar(QString m_eventText, QDateTime m_dateTime);
    ~Calendar();

    //Getters

    inline QString eventText() const {return m_eventText;}
    inline QDateTime dateTime() {return m_dateTime;}

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

private:
    QString m_eventText;
    QDateTime m_dateTime;
};

#endif // CALENDAR_H
