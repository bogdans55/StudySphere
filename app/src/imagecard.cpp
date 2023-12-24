#include "lib/imagecard.h"

ImageCard::ImageCard() : Card() {}

ImageCard::ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty)
	: Card(questionText, answerText, questionDifficulty)
{}

ImageCard::ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty, QPixmap questionImage,
                     QPixmap answerImage)
	: Card(questionText, answerText, questionDifficulty), m_questionImage(questionImage), m_answerImage(answerImage)
{}

ImageCard::~ImageCard() {}

void ImageCard::setQuestionImage(const QPixmap &questionImage)
{
	m_questionImage = questionImage;
}

void ImageCard::setAnswerImage(const QPixmap &answerImage)
{
	m_answerImage = answerImage;
}
