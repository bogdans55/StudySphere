#include "lib/libraryscene.h"
#include "lib/deck.h"
#include "lib/deckitem.h"

LibraryScene::LibraryScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

void LibraryScene::addDeck(DeckItem *deckItem)
{
    const auto sirinaTable = static_cast<int>(this->width());
    const auto visinaTable = static_cast<int>(this->height());
    auto xPozPomeraj = 0.0;
    auto indeksNovogCvora = m_decks.size();

//    adding under
//    const auto xPoz = (120 * indeksNovogCvora) % sirinaTable;
//    const auto yPoz = 200 * ((120 * indeksNovogCvora) / sirinaTable);
//    deckItem->setPos(xPoz + xPozPomeraj, yPoz);

//    adding to the right
    const auto yPoz = (200 * indeksNovogCvora) % visinaTable;
    const auto xPoz = 120 * ((200 * indeksNovogCvora) / visinaTable);
    deckItem->setPos(xPoz + xPozPomeraj, yPoz);
}
