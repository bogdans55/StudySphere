#ifndef PLNNER_H
#define PLNNER_H

#include <QJsonObject>
#include "lib/serializable.h"

class Planner : public Serializable
{
public:
    Planner();
    Planner(QString m_activityText, QString m_start, QString m_end, QString m_day);
    ~Planner();

    //Getters
    inline QString activityText() const {return m_activityText;}
    inline QString start() const {return m_start;}
    inline QString end() const {return m_end;}
    inline QString day() const {return m_day;}

    void fromJson(const QJsonObject& json);
    QJsonObject toJson() const;

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;


protected:
    QString m_activityText;
    QString m_start;
    QString m_end;
    QString m_day;
};



#endif // PLNNER_H
