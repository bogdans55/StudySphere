#include "../lib/plannerscene.h"

PlannerScene::PlannerScene(QObject *parent) : QGraphicsScene{parent}
{
	m_activityColors.push_back(QColor::fromRgb(119, 158, 204));
	m_activityColors.push_back(QColor::fromRgb(159, 192, 222));
	m_activityColors.push_back(QColor::fromRgb(242, 200, 148));
	m_activityColors.push_back(QColor::fromRgb(255, 179, 71));
	m_activityColors.push_back(QColor::fromRgb(255, 152, 90));
	m_colorPicker = 0;
}

void PlannerScene::addActivity(ActivityItem *activityItem)
{
	const auto yPos = activityItem->activity().start().hour() * 60 + activityItem->activity().start().minute();

	activityItem->setPos(0, yPos);
	activityItem->setWidth(this->width());

	activityItem->setColor(m_activityColors[m_colorPicker]);
	m_colorPicker++;
	m_colorPicker %= m_activityColors.size();

	m_activities.push_back(activityItem->activity());
}

void PlannerScene::clearActivities()
{
	m_activities.clear();
}
