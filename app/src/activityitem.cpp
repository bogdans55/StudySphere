#include "../lib/activityitem.h"
#include <QPainter>
#include <QTextDocument>

ActivityItem::ActivityItem(Activity activity) : QGraphicsItem(), m_activity(activity) {}

QRectF ActivityItem::boundingRect() const
{
	return {0, 0, m_width, height()};
}

void ActivityItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option)
	Q_UNUSED(widget)

	painter->fillRect(boundingRect(), m_color);
	painter->drawRect(boundingRect());
}

void ActivityItem::setWidth(unsigned int width)
{
	m_width = width;
}

void ActivityItem::setColor(QColor color)
{
	m_color = color;
}
