#include "lib/deck.h"
#include <QJsonArray>
#include <QRandomGenerator>
#include <QString>

Deck::Deck() : m_deckId(), m_privacy() {}

Deck::Deck(const QString &name, const User &user, Privacy privacy)
    : m_deckId(0), m_name(name), m_privacy(privacy), m_user(user), m_cards()
{}

Deck::Deck(const Deck &deck)
	: m_deckId(deck.m_deckId), m_name(deck.m_name), m_cards(deck.m_cards), m_privacy(deck.m_privacy),
      m_user(deck.m_user)
{}

Deck::~Deck()
{
	for (Card *card : m_cards)
		delete card;
}

void Deck::addCard(Card *card)
{
	m_cards.append(card);
}

bool Deck::operator==(const Deck &deck)
{
	return this->deckId() == deck.deckId();
}

QVariant Deck::toVariant() const
{
	QVariantMap map;
	map.insert("DeckId", static_cast<int>(deckId()));
	map.insert("Subject", name());
    map.insert("Privacy", (privacy() == Privacy::PRIVATE) ? "Private" : "Public");

	QVariantList cardsList;
	for (int i = 0; i < m_cards.length(); i++) {
		Card card = *(m_cards[i]);
		cardsList.append(card.toVariant());
	}
	map.insert("Flashcards", cardsList);
	map.insert("User", m_user.toVariant());

	return map;
}

void Deck::fromVariant(const QVariant &variant)
{
	QVariantMap map = variant.toMap();
	m_deckId = map.value("DeckId").toUInt();
	m_name = map.value("Subject").toString();
	if (map.value("Privacy").toString() == "Private") {
		m_privacy = Privacy::PRIVATE;
	}
	else {
		m_privacy = Privacy::PUBLIC;
	}

	m_cards.clear();

	QVariantList cardsVariantList = map.value("Flashcards").toList();
    for (const QVariant &card : cardsVariantList) {
        Card *currCard = new Card();
		currCard->fromVariant(card);
		m_cards.push_back(currCard);
    }

	m_user.fromVariant(map.value("User"));
}

void Deck::setId(uint64_t id)
{
	m_deckId = id;
}
