#ifndef LIBRARYALT_H
#define LIBRARYALT_H

#include "lib/deckitem.h"

class Deck;
class DectItem;

#include <QGraphicsScene>

class LibraryAlt : public QGraphicsScene
{
public:
    explicit LibraryAlt(QObject *parent = nullptr);

    QVector<Deck *> m_decks;
    void addDeck(DeckItem *deckItem);
private:

};

#endif // LIBRARYALT_H
