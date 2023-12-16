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

    inline unsigned width() const { return 100; }
    inline unsigned height() const { return m_activity.start().secsTo(m_activity.end()) / 60; }

    inline Activity activity() const { return m_activity; }

private:
    Activity m_activity;
};

#endif // ACTIVITYITEM_H
