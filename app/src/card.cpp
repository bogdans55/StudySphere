#include <utility>

#include "../lib/card.h"

Card::Card() : m_questionText(), m_answerText(), m_questionDifficulty() {}

Card::Card(QString questionText, QString answerText, Difficulty questionDifficulty)
	: m_questionText(std::move(questionText)), m_answerText(std::move(answerText)),
	  m_questionDifficulty(questionDifficulty)
{}

Card::Card(const Card &card)
	: m_questionText(card.m_questionText), m_answerText(card.m_answerText),
	  m_questionDifficulty(card.m_questionDifficulty)
{}

Card::~Card() = default;

QVariant Card::toVariant() const
{
	QVariantMap map;
	map.insert("question", m_questionText);
	map.insert("answer", m_answerText);
	QString difficultyStr;
	switch (m_questionDifficulty) {
	case Difficulty::EASY:
		difficultyStr = "EASY";
		break;
	case Difficulty::MEDIUM:
		difficultyStr = "MEDIUM";
		break;
	case Difficulty::HARD:
		difficultyStr = "HARD";
		break;
	default:
		difficultyStr = "MEDIUM";
		break;
	}
	map.insert("difficulty", difficultyStr);
	return map;
}

void Card::fromVariant(const QVariant &variant)
{
	QVariantMap map = variant.toMap();
	m_questionText = map.value("question").toString();
	m_answerText = map.value("answer").toString();
	QString questionDifficultyStr = map.value("difficulty").toString();
	if (questionDifficultyStr == "EASY") {
		m_questionDifficulty = Difficulty::EASY;
	}
	else if (questionDifficultyStr == "MEDIUM") {
		m_questionDifficulty = Difficulty::MEDIUM;
	}
	else if (questionDifficultyStr == "HARD") {
		m_questionDifficulty = Difficulty::HARD;
	}
}
