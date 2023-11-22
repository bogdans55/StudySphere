#ifndef LIBRARY_H
#define LIBRARY_H

#include <QString>
#include <QVector>
#include "deck.h"
#include <QImage>

class Library{

public:
    static Library& getInstance();

    void addDeck(const Deck& deck);
    void removeDeck(const QVector<Deck>& decks);
    void importDeck(const QString& filePath);
    void exportDeck(const QVector<Deck>& decks, const QString& filePath);
private:
    QVector<Deck> m_decks;

    Library();
    Library(const Library&) = delete;
    void operator=(const Library&) = delete;
};

#endif // LIBRARY_H
