#ifndef PLAINCARD_H
#define PLAINCARD_H

#include "card.h"

class PlainCard : public Card
{
  public:
	PlainCard();
	PlainCard(QString questionText, QString answerText, Difficulty questionDifficulty);
	~PlainCard() override;

  private:
};

#endif // PLAINCARD_H
