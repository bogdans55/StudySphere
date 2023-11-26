#include "lib/library.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QJsonArray>


Library::Library(){
    //TODO delete hardcoded path, and make so that user can define path where the decks will be stored
    loadDecksFromFolder("../sampleData/privateDecks");
}

Library& Library::getInstance(){
    static Library instance;
    return instance;
}

void Library::addDeck(const Deck& deck)
{
    m_decks.push_back(deck);
}

void Library::loadDecksFromFolder(const QString folderPath){
    QDir deckFolder(folderPath);

    QStringList nameFilters;
    nameFilters << "*.json";
    deckFolder.setNameFilters(nameFilters);

    QStringList deckFiles = deckFolder.entryList();

    for(const QString& deckFile : deckFiles){
        QString filePath = deckFolder.filePath(deckFile);
        importDeck(filePath);
    }
}

void Library::removeDeck(QVector<Deck>& decks){
    for(Deck& deck : decks){

        for(int i = 0;i < m_decks.length();i++){
            if(m_decks[i] == deck)
                m_decks.remove(i);
        }

        QString filePath = deck.getFilePath();

        QFile file(filePath);
        if(file.remove()){
            qDebug() << "File removed: " << filePath;
        }
        else{
            qDebug() << "Failed to remove file: " << filePath;
            //TODO error handling if needed...
        }
    }
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








