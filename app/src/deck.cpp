#include "lib/deck.h"
#include <QJsonArray>
#include <QRandomGenerator>
#include <QString>

Deck::Deck()
    : m_deckId(-1),
    m_privacy(),
    m_deckStats(),
    m_thumbnail(),
    m_rating(),
    m_numOfCardsPerTest()
{}

Deck::Deck(const QString &name, Privacy privacy, unsigned int numOfCardsPerTest, const QImage &thumbnail)
    : m_deckId(0),
    //TODO Smart Id choosing
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(thumbnail),
    m_rating(),
    m_numOfCardsPerTest(numOfCardsPerTest)
{}

Deck::Deck(const QString &name, Privacy privacy, unsigned int numOfCardsPerTest)
    : m_deckId(0),
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(),
    m_rating(),
    m_numOfCardsPerTest(numOfCardsPerTest)
{}

Deck::Deck(const QString &name, Privacy privacy)
    : m_deckId(0),
    m_name(name),
    m_privacy(privacy),
    m_deckStats(),
    m_thumbnail(),
    m_rating(),
    m_numOfCardsPerTest(20)
{}

void Deck::addCard(Card card)
{
    m_cards.append(card);
}

void Deck::updateRating(unsigned int grade)
{
    m_rating.addNewGrade(grade);
}

void Deck::setId(uint64_t id){
    m_deckId = id;
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
    json["DeckID"] = static_cast<int>(deckId());
    json["Subject"] = name();
    json["Privacy"] = (privacy() == Privacy::PRIVATE) ? "Private" : "Public";
    json["Thumbnail"] = "systemDefault.png";
    //TODO Thumbnail image saving, and naming
    json["NumberOfCardsPerIteration"] = static_cast<int>(numOfCardsPerTest());
    //TODO add real user
    json["Username"] = "defaultUser";
    //TODO add real rating
    json["DeckRating"] = 0.0;

    QJsonArray cardsArray;
    for(const Card& card : cards()){
        cardsArray.append(card.toJson());
    }
    json["Flashcards"] = cardsArray;
    return json;
}

QString Deck::getFilePath(){
    return  QString::number(deckId()).append(".json");
}

bool Deck::operator==(const Deck& deck){return this->deckId() == deck.deckId();}

QVariant Deck::toVariant() const{
    QVariantMap map;
    map.insert("DeckId", static_cast<int>(deckId()));
    map.insert("Subject", name());
    map.insert("Privacy", (privacy() == Privacy::PRIVATE) ? "Private" : "Public");
    map.insert("Thumbnail", "systemDefault.png");     //TODO Thumbnail image saving, and naming
    map.insert("NumberOfCardsPerIteration", static_cast<int>(numOfCardsPerTest()));
    //TODO add real User
    map.insert("Username", "defaultUser");
    //TODO add real deck rating
    map.insert("DeckRating", 0.0);
    QVariantList cardsList;
    for (const Card &card : m_cards){ //cards?
        cardsList.append(card.toVariant());
        }
    map.insert("Flashcards", cardsList);

    return map;
}

void Deck::fromVariant(const QVariant &variant){
    QVariantMap map = variant.toMap();
    m_deckId = map.value("DeckId").toUInt();
    m_name = map.value("Subject").toString();
    if(map.value("Privacy").toString() == "Private"){
        m_privacy = Privacy::PRIVATE;
    }
    else{
        m_privacy = Privacy::PUBLIC;
    }
    m_thumbnail = QImage(map.value("Thumbnail").toString());
    m_numOfCardsPerTest = map.value("NumOfCardsPerIteration").toUInt();

    //qDeleteAll(&m_cards);
    m_cards.clear();

    const auto cards = map.value("Flashcards").toList();
    for(const auto &card : cards){
        Card curr_card;
        curr_card.fromVariant(card);
        m_cards.push_back(curr_card);
    }
}









