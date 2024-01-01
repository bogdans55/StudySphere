#ifndef IMAGECARD_H
#define IMAGECARD_H

#include "card.h"
#include <QImage>

class ImageCard : public Card
{
  public:
	ImageCard();
	ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty);
	ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty, QImage questionImage,
			  QImage answerImage);
	~ImageCard() override;

	inline QImage questionImage() const { return m_questionImage; }

	inline QImage answerImage() const { return m_answerImage; }

	void setQuestionImage(const QImage &questionImage);
	void setAnswerImage(const QImage &answerImage);

  private:
	QImage m_questionImage;
	QImage m_answerImage;
};

#endif // IMAGECARD_H
