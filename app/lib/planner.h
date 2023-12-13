#ifndef PLANNER_H
#define PLANNER_H

#include "lib/activity.h"
#include "lib/serializable.h"
#include <QVector>
#include <QMap>

enum class Day
{
    MONDAY = 0 ,
    TUESDAY ,
    WEDNESDAY ,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};


class Planner : public Serializable
{
private:

    QMap <Day, QVector<Activity>> m_map;

public:
    Planner();
    ~Planner();

    QVariant toVariant() const override;
    void fromVariant(const QVariant &variant) override;

    void addActivity(Activity activity, Day day);

};

#endif // PLANNER_H
