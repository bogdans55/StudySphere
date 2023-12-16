#include "lib/activityitem.h"
#include <QTextDocument>
#include <QPainter>

ActivityItem::ActivityItem(Activity activity)
    : QGraphicsItem(),
    m_activity(activity)
{

}

QRectF ActivityItem::boundingRect() const
{
    return QRectF(0, 0, width(), height());
}

void ActivityItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(boundingRect(), QColor::fromRgb(0, 128, 255));
//    painter->drawText(boundingRect(), Qt::AlignVCenter, m_activity.activityText());
}
