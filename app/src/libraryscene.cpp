#include "lib/libraryscene.h"
#include "lib/deck.h"
#include "lib/deckitem.h"

LibraryScene::LibraryScene(QObject *parent) : QGraphicsScene(parent) {}

void LibraryScene::addDeck(DeckItem *deckItem)
{
	//    const auto tableWidth = static_cast<int>(this->width());
	const auto tableHeight = static_cast<int>(this->height());
	auto currentIndex = m_decks.size();

	//    auto offset = m_decks.size() == 0 ? 0 : 20;
	const auto offset = 20;

	//    adding to the right
	const auto yPos = (deckItem->height() * currentIndex) % tableHeight;
	const auto xPos = deckItem->width() * ((deckItem->height() * currentIndex) / tableHeight);
	deckItem->setPos(xPos + currentIndex * offset, yPos);

	m_decks.push_back(deckItem->deck());
}

void LibraryScene::clearDeck()
{
	m_decks.clear();
}
