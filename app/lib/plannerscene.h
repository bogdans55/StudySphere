#ifndef PLANNERSCENE_H
#define PLANNERSCENE_H

#include "lib/activity.h"
#include <QGraphicsScene>
#include <QMap>

#define MONDAY      (1)
#define TUESDAY     (2)
#define WEDNESDAY   (3)
#define THURSDAY    (4)
#define FRIDAY      (5)
#define SATURDAY    (6)
#define SUNDAY      (7)

class PlannerScene : public QGraphicsScene
{
public:
    explicit PlannerScene(QObject *parent = nullptr);

    inline auto activities() const { return m_activities; }

private:
    QMap<int, QVector<Activity>> m_activities; // values should be vector of activites?
};

#endif // PLANNERSCENE_H
