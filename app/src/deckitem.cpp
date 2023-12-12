#include "lib/deckitem.h"
#include <QPainter>

DeckItem::DeckItem(Deck *deck)
    : QGraphicsItem()
    , m_deck(*deck)
{

}

QRectF DeckItem::boundingRect() const
{
    return QRectF(0, 0, 200, 500); // hardcoded values for test purposess
}

void DeckItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->fillRect(boundingRect(), QColor::fromRgb(0, 128, 255));
    painter->setPen(QPen(Qt::black, 1));
    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), Qt::AlignHCenter | Qt::AlignVCenter, m_deck.name());
}
