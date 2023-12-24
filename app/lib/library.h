#ifndef LIBRARY_H
#define LIBRARY_H

#include "deck.h"
#include <QImage>
#include <QString>
#include <QVector>

class Library
{

  public:
	static Library &instance();

	void addDeck(const Deck &deck);
	void removeDeck(Deck &deck, QString &username);
	void importDeck(const QString &filePath);
	void exportDeck(const QVector<Deck> &decks, const QString &filePath);

  private:
	QVector<Deck> m_decks;

	Library();
	Library(const Library &) = delete;
	void operator=(const Library &) = delete;

	void loadDecksFromFolder(const QString folderPath);
};

#endif // LIBRARY_H
