#ifndef PLANNERSCENE_H
#define PLANNERSCENE_H

#include "activityitem.h"
#include <QGraphicsScene>
#include <QMap>

class PlannerScene : public QGraphicsScene
{
  public:
	explicit PlannerScene(QObject *parent = nullptr);

	inline auto activities() const { return m_activities; }

	void addActivity(ActivityItem *activityItem);
	void clearActivities();

  private:
	QVector<Activity> m_activities;
	QVector<QColor> m_activityColors;
	unsigned m_colorPicker;
};

#endif // PLANNERSCENE_H
