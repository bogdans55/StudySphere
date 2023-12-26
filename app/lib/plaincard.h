#ifndef PLAINCARD_H
#define PLAINCARD_H

#include "lib/card.h"

class PlainCard : public Card
{
  public:
	PlainCard();
	PlainCard(QString questionText, QString answerText, Difficulty questionDifficulty);
	~PlainCard();

	//    // override
	//    void flipCard() override;
	//    void evaluateAnswer(unsigned evaluation) override;

  private:
};

#endif // PLAINCARD_H
