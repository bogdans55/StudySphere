#include "../lib/studysession.h"
#include "../lib/jsonserializer.h"
#include "../lib/servercommunicator.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QTcpServer>
#include <QTcpSocket>
#include <algorithm>
#include <numeric>
#include <random>

StudySession::StudySession() : m_user(), m_deck() {}

StudySession::StudySession(const User &user, Deck *deck) : m_user(user), m_deck(deck) {}

StudySession::StudySession(const StudySession &session)
	: m_user(session.m_user), m_deck(session.m_deck), m_cardSequence(session.m_cardSequence),
	  m_currentCardIndex(session.m_currentCardIndex), m_timeStarted(session.m_timeStarted),
	  m_timeEnded(session.m_timeEnded), m_answerShowed(session.m_answerShowed)
{}

StudySession::~StudySession()
{
	delete m_deck;
	delete m_deckStats;
}

void StudySession::startSession()
{
	m_timeStarted = time(nullptr);

	QJsonObject requestObject;

	requestObject["action"] = "getStats";
	requestObject["username"] = m_user.username();
	requestObject["DeckId"] = QString::number(m_deck->deckId());

	ServerCommunicator communicator;

	QJsonDocument request(requestObject);

	QJsonObject statsObject = communicator.sendRequest(request);
	QJsonDocument statsDocument = QJsonDocument::fromVariant(statsObject.toVariantMap());

	if (statsObject["status"].toString() == "no stats") {
		m_deckStats = new DeckStats(m_deck->cards().length());
	}
	else {
		JSONSerializer jsonSerializer;
		m_deckStats = new DeckStats();
		jsonSerializer.loadJson(*m_deckStats, statsDocument);
	}

	this->chooseCardSequence(m_deck->cards().length());
}

void StudySession::endSession()
{
	m_timeEnded = time(nullptr);
	m_deckStats->usedDeck();
}

void StudySession::chooseCardSequence(unsigned numCards)
{
	QVector<unsigned> cardIndices(numCards);
	QVector<bool> visited(numCards);
	for (unsigned i = 0; i < numCards; i++) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::vector<double> probabilities = {0.4, 0.3, 0.2, 0.1};
		std::discrete_distribution<> distribution(probabilities.begin(), probabilities.end());
		QVector<unsigned> cardPersonalDiffIndices;
		while (cardPersonalDiffIndices.isEmpty()) {
			unsigned difficulty = distribution(gen);
			for (unsigned j = 0; j < numCards; j++) {
				auto grades = m_deckStats->grades();
				if (grades[j] == difficulty && !visited[j])
					cardPersonalDiffIndices.append(j);
			}
		}
		unsigned selectedIndex = QRandomGenerator::global()->bounded(cardPersonalDiffIndices.size());
		visited[cardPersonalDiffIndices[selectedIndex]] = true;
		cardIndices[i] = cardPersonalDiffIndices[selectedIndex];
	}
	m_currentCardIndex = 0;
	m_cardSequence = cardIndices;
}

void StudySession::nextCard()
{
	m_currentCardIndex++;
	m_answerShowed = false;
}

Card StudySession::getCurrentCard()
{
	auto cards = m_deck->cards();
	return *cards[m_cardSequence[m_currentCardIndex]];
}

void StudySession::flipCard()
{
	m_answerShowed = !m_answerShowed;
}

bool StudySession::hasNextCard()
{
	return m_currentCardIndex + 1 < m_cardSequence.length();
}
