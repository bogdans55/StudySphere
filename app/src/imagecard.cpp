#include <utility>

#include <utility>

#include "../lib/imagecard.h"

ImageCard::ImageCard() : Card() {}

ImageCard::ImageCard(QString questionText, QString answerText, Difficulty questionDifficulty)
    : Card(std::move(questionText), std::move(answerText), questionDifficulty)
{}

ImageCard::ImageCard(QString questionText,
                     QString answerText,
                     Difficulty questionDifficulty,
                     QImage questionImage,
                     QImage answerImage)
    : Card(std::move(questionText), std::move(answerText), questionDifficulty)
    , m_questionImage(std::move(std::move(questionImage)))
    , m_answerImage(std::move(answerImage))
{}

ImageCard::~ImageCard() = default;

void ImageCard::setQuestionImage(const QImage &questionImage)
{
	m_questionImage = questionImage;
}

void ImageCard::setAnswerImage(const QImage &answerImage)
{
	m_answerImage = answerImage;
}
