#include "lib/browser.h"
#include "lib/deck.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Browser::Browser(const QString& publicDecksFolder, Library& library)
    : m_publicDecksFolder(publicDecksFolder),
    m_library(library)
{}

void Browser::loadPublicDecks(){
    QDir deckFolder(m_publicDecksFolder);

    QStringList nameFilters;
    nameFilters << "*.json";
    deckFolder.setNameFilters(nameFilters);

    QStringList deckFiles = deckFolder.entryList();

    for(const QString& deckFile : deckFiles){
        QString filePath = deckFolder.filePath(deckFile);
        importDeck(filePath);
    }
}


void Browser::importDeck(QString& filePath){

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        QJsonArray deckArray = document.array();

        for(const QJsonValue& deckValue : deckArray){
            Deck deck;
            deck.fromJson(deckValue.toObject());
            m_publicDeckList.push_back(deck);
        }
        file.close();
    }
}

void Browser::searchDecks(const QString& searchQuery){
    m_foundDecks.erase(m_foundDecks.begin(), m_foundDecks.end());
    for(int i = 0; i < m_publicDeckList.size(); i++){
        if(searchQuery == QString::number(m_publicDeckList[i].deckId())){
            m_foundDecks.push_back(m_publicDeckList[i]);
        }
    }
}

void Browser::addDeckToLibrary(Deck& deck){
    m_library.addDeck(deck);
}
