#include "lib/library.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>


Library::Library(){
    //Initialize the library instance, load decks from json...
}

Library& Library::getInstance(){
    static Library instance;
    return instance;
}

void Library::addDeck(const Deck& deck)
{
    m_decks.push_back(deck);
}

void Library::removeDeck(const QVector<Deck>& decks){
    for(const Deck& deck : decks){
        m_decks.removeAll(deck);
    }
    //TODO update library document, so the decks that were removed are removed from the document also
}

void Library::importDeck(const QString& filePath){

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        QJsonArray deckArray = document.array();

        for(const QJsonValue& deckValue : deckArray){
            Deck deck;
            deck.fromJson(deckValue.toObject());
            m_decks.push_back(deck);
        }
        file.close();
    }
}

void Library::exportDeck(const QVector<Deck>& decks, const QString& filePath){
    QJsonArray deckArray;
    for(const Deck& deck : decks){
        deckArray.append(deck.toJson());
    }

    QJsonDocument document(deckArray);

    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.write(document.toJson());
        file.close();
    }
}








