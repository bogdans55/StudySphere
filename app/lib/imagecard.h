#ifndef IMAGECARD_H
#define IMAGECARD_H

#include "card.h"
#include <QImage>
#include <QPixmap>

class ImageCard : public Card
{
  public:
	ImageCard();
	ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty);
    ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty, QPixmap questionImage,
              QPixmap answerImage);
	~ImageCard();

	// Getters
    inline QPixmap questionImage() const { return m_questionImage; }

    inline QPixmap answerImage() const { return m_answerImage; }

    void setQuestionImage(const QPixmap &questionImage);
    void setAnswerImage(const QPixmap &answerImage);

  private:
    QPixmap m_questionImage;
    QPixmap m_answerImage;
};

#endif // IMAGECARD_H
