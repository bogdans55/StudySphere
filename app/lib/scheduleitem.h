#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QGraphicsItem>

class ScheduleItem : public QGraphicsItem
{
public:
    ScheduleItem();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // hardcoded
    inline int width() const { return 100; }    // horizontal scroll is off so we can use large values
    inline int height() const { return 1440; }
};

#endif // SCHEDULEITEM_H
