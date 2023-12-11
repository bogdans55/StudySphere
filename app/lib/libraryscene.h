#ifndef LIBRARYSCENE_H
#define LIBRARYSCENE_H

#include "lib/deckitem.h"

class Deck;
class DectItem;

#include <QGraphicsScene>

class LibraryScene : public QGraphicsScene
{
public:
    explicit LibraryScene(QObject *parent = nullptr);

    QVector<Deck *> m_decks;
    void addDeck(DeckItem *deckItem);
private:

};

#endif // LIBRARYSCENE_H
