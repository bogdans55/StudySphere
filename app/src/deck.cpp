#include "lib/deck.h"
#include <QJsonArray>
#include <QRandomGenerator>
#include <QString>

Deck::Deck() : m_deckId(), m_privacy(), m_deckStats(), m_thumbnail(), m_rating() {}

Deck::Deck(const QString &name, Privacy privacy, const QImage &thumbnail)
	: m_deckId(0),
	  // TODO Smart Id choosing
	  m_name(name), m_privacy(privacy), m_deckStats(), m_thumbnail(thumbnail), m_rating()
{}

Deck::Deck(const QString &name, Privacy privacy)
	: m_deckId(0), m_name(name), m_privacy(privacy), m_deckStats(), m_thumbnail(), m_rating()
{}

Deck::Deck(const Deck &deck)
	: m_deckId(deck.m_deckId), m_name(deck.m_name), m_cards(deck.m_cards), m_privacy(deck.m_privacy),
	  m_deckStats(deck.m_deckStats), m_thumbnail(deck.m_thumbnail), m_rating(deck.m_rating)
{}

void Deck::addCard(Card *card)
{
	m_cards.append(card);
}

void Deck::updateRating(unsigned int grade)
{
	m_rating.addNewGrade(grade);
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
	map.insert("Thumbnail", "systemDefault.png"); // TODO Thumbnail image saving, and naming

	QVariantList cardsList;

	for (int i = 0; i < m_cards.length(); i++) {
		Card card = *(m_cards[i]);
		cardsList.append(card.toVariant());
	}

	map.insert("Flashcards", cardsList);

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
	m_thumbnail = QImage(map.value("Thumbnail").toString());

	// qDeleteAll(&m_cards);
	m_cards.clear();

	QVariantList cardsVariantList = map.value("Flashcards").toList();
	for (QVariant card : cardsVariantList) {
		Card *curr_card = new Card();
		curr_card->fromVariant(card);
		qDebug() << curr_card->questionText();
		m_cards.push_back(curr_card);
	}
}

void Deck::setId(uint64_t id)
{
	m_deckId = id;
}
