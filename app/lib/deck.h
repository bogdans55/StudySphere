#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "user.h"
#include <QImage>
#include <QString>
#include <QVector>

enum Privacy
{
	PRIVATE,
	PUBLIC
};

class Deck : public Serializable
{
  private:
	unsigned m_deckId;
	QString m_name;
	QVector<Card *> m_cards;
	Privacy m_privacy;
	User m_user;

  public:
	Deck();
	Deck(QString name, const User &user, Privacy privacy);
	Deck(const Deck &deck);
	~Deck() override;

	inline unsigned int deckId() const { return m_deckId; }

	inline QString name() const { return m_name; }

	inline QVector<Card *> cards() { return m_cards; }

	inline Privacy privacy() const { return m_privacy; }

	inline User user() const { return m_user; }

	void addCard(Card *card);
	void setId(uint64_t id);

    bool operator==(const Deck &deck);

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;
};

#endif // DECK_H
