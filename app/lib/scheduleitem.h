#ifndef SCHEDULEITEM_H
#define SCHEDULEITEM_H

#include <QGraphicsItem>

class ScheduleItem : public QGraphicsItem
{
  public:
	ScheduleItem();

	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	inline unsigned width() const { return m_width; }

	inline unsigned height() const { return 1440; }

	void setWidth(unsigned width);

  private:
	unsigned m_width = 180;
};

#endif // SCHEDULEITEM_H
