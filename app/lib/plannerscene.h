#ifndef PLANNERSCENE_H
#define PLANNERSCENE_H

#include "lib/activityitem.h"
#include <QGraphicsScene>
#include <QMap>

class PlannerScene : public QGraphicsScene
{
public:
    explicit PlannerScene(QObject *parent = nullptr);

    inline auto activities() const { return m_activities; }

    void addActivity(ActivityItem *activityItem);

private:
    QVector<Activity> m_activities;
};

#endif // PLANNERSCENE_H
