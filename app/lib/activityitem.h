#ifndef ACTIVITYITEM_H
#define ACTIVITYITEM_H

#include "lib/activity.h"
#include <QGraphicsItem>

class ActivityItem : public QGraphicsItem
{
public:
    ActivityItem();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    Activity m_activity;
};

#endif // ACTIVITYITEM_H
