#include "lib/deck.h"
#include <QJsonArray>
#include <QRandomGenerator>

Deck::Deck(const QString &name, Privacy privacy, unsigned int numOfCardsPerTest, const QImage &thumbnail)
    : m_deckId(QRandomGenerator::global()->generate()),
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(thumbnail),
    m_rating(),
    m_numOfCardsPerTest(numOfCardsPerTest)
{}

Deck::Deck(const QString &name, Privacy privacy, unsigned int numOfCardsPerTest)
    : m_deckId(QRandomGenerator::global()->generate()),
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(),
    m_rating(),
    m_numOfCardsPerTest(numOfCardsPerTest)
{}


void Deck::addCard(Card card)
{
    m_cards.append(card);
}

void Deck::updateRating(unsigned int grade)
{
    m_rating.addNewRating(grade);
}

void Deck::fromJson(const QJsonObject& json){
    m_deckId = json["DeckID"].toVariant().toUInt();
    m_name = json["Subject"].toString();
    if(json["Subject"].toString() == "Private"){
        m_privacy = Privacy::PRIVATE;
    }
    else{
        m_privacy = Privacy::PUBLIC;
    }
    m_thumbnail = QImage(json["Thumbnail"].toString());
    m_numOfCardsPerTest = json["NumOfCardsPerIteration"].toVariant().toUInt();

    m_cards.clear();
    QJsonArray cardsArray = json["FlashCards"].toArray();
    for(const QJsonValue& cardValue : cardsArray){
        Card card;
        card.toJson();
        m_cards.push_back(card);
    }
}

QJsonObject Deck::toJson() const{
    QJsonObject json;
    json["DeckID"] = static_cast<int>(m_deckId);
    json["Subject"] = m_name;
    json["Privacy"] = (m_privacy == Privacy::PRIVATE) ? "Private" : "Public";
    json["Thumbnail"] = "systemDefault.png";
    //TODO Thumbnail image saving, and naming
    json["NumberOfCardsPerIteration"] = static_cast<int>(m_numOfCardsPerTest);

    QJsonArray cardsArray;
    for(const Card& card : m_cards){
        cardsArray.append(card.toJson());
    }
    json["Flashcards"] = cardsArray;
    return json;
}













