#include "lib/libraryscene.h"
#include "lib/deck.h"
#include "lib/deckitem.h"

LibraryScene::LibraryScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void LibraryScene::addDeck(DeckItem *deckItem)
{
    const auto tableWidth = static_cast<int>(this->width());
    const auto tableHeight = static_cast<int>(this->height());
    auto currentIndex = m_decks.size();

//    adding under
//    const auto xPoz = (120 * currentIndex) % tableWidth;
//    const auto yPoz = 200 * ((120 * currentIndex) / tableWidth);
//    deckItem->setPos(xPoz + offset, yPoz);

//    adding to the right
    const auto yPos = (500 * currentIndex) % tableHeight;
    const auto xPos = 200 * ((500 * currentIndex) / tableHeight);
    deckItem->setPos(xPos, yPos);
}
