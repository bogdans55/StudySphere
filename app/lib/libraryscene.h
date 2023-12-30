#ifndef LIBRARYSCENE_H
#define LIBRARYSCENE_H

#include "deckitem.h"

class Deck;
class DectItem;

#include <QGraphicsScene>

class LibraryScene : public QGraphicsScene
{
  public:
	explicit LibraryScene(QObject *parent = nullptr);

	inline QVector<Deck> decks() const { return m_decks; }

	void addDeck(DeckItem *deckItem);
	void clearDeck();

  private:
	QVector<Deck> m_decks;
};

#endif // LIBRARYSCENE_H
