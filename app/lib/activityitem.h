#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H

#include "lib/activity.h"
#include <QGraphicsItem>

class ActivityItem : public QGraphicsItem
{
  public:
	ActivityItem(Activity activity);

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	inline unsigned width() const { return m_width; }

	inline unsigned height() const { return m_activity.start().secsTo(m_activity.end()) / 60; }

	void setWidth(unsigned width);
	void setColor(QColor color);

	inline Activity activity() const { return m_activity; }

  private:
	Activity m_activity;

	unsigned m_width;

	QColor m_color;
};

#endif // ACTIVITYITEM_H
