#ifndef DECKITEM_H
#define DECKITEM_H

#include "lib/deck.h"
#include <QGraphicsItem>

class Deck;

class DeckItem : public QGraphicsItem
{
public:
    DeckItem(Deck *deck);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    inline int width() const { return 200; }
    inline int height() const { return 500; }

    inline Deck deck() const { return m_deck; }

private:
    Deck m_deck;
};

#endif // DECKITEM_H
