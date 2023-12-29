#include "lib/studysession.h"
#include "lib/jsonserializer.h"
#include <QDebug>
#include <QRandomGenerator>
#include <algorithm>
#include <numeric>
#include <random>
#include <QTcpSocket>
#include <QTcpServer>
#include <QJsonDocument>
#include <QJsonObject>

StudySession::StudySession() : m_user(), m_deck() {}

StudySession::StudySession(const User &user, Deck *deck) : m_user(user), m_deck(deck) {}

StudySession::StudySession(const StudySession &session)
	: m_user(session.m_user), m_deck(session.m_deck), m_cardSequence(session.m_cardSequence),
      m_currentCardIndex(session.m_currentCardIndex), m_timeStarted(session.m_timeStarted),
    m_timeEnded(session.m_timeEnded), m_answerShowed(session.m_answerShowed)
{}

StudySession::~StudySession() {}

void StudySession::startSession()
{
	m_timeStarted = time(NULL);

	QTcpSocket socket;
	socket.connectToHost("127.0.0.1", 8080);

	if (socket.waitForConnected()) {
		QJsonObject request;

		request["action"] = "getStats";
		request["username"] = m_user.username();
		request["DeckId"] = QString::number(m_deck->deckId());

		socket.write(QJsonDocument(request).toJson());
		socket.waitForBytesWritten();
		socket.waitForReadyRead();
		QByteArray statsResponse = socket.readAll();
		QTextStream statsStream(statsResponse);

		QString statsResponseString = statsStream.readAll();
		QJsonDocument statsJson = QJsonDocument::fromJson(statsResponseString.toUtf8());
		QJsonObject statsObject = statsJson.object();

		socket.disconnectFromHost();

		if(statsObject["status"].toString() == "no stats"){
			m_deckStats = new DeckStats(m_deck->cards().length());
		}
		else{
			JSONSerializer jsonSerializer;
			m_deckStats = new DeckStats();
			jsonSerializer.loadJson(*m_deckStats, statsJson);
		}
	}
	else {
		qDebug() << "Failed to connect to the server";
	}

	this->chooseCardSequence(m_deck->cards().length());
}

void StudySession::endSession()
{
	m_timeEnded = time(NULL);
    m_deckStats->usedDeck();
}

void StudySession::chooseCardSequence(unsigned numCards)
{
	qDebug() << m_deckStats->grades();
	QVector<unsigned> cardIndices(numCards);
	QVector<bool> visited(numCards);
	for (unsigned i = 0;i < numCards;i++){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::vector<double> probabilities = {0.4, 0.3, 0.2, 0.1};
		std::discrete_distribution<> distribution(probabilities.begin(), probabilities.end());
		QVector<unsigned> cardPersonalDiffIndices;
		while(cardPersonalDiffIndices.isEmpty()){
			unsigned difficulty = distribution(gen);
			for (unsigned j = 0;j < numCards;j++)
				if(m_deckStats->grades()[j] == difficulty && !visited[j])
					cardPersonalDiffIndices.append(j);
		}
		qDebug() << cardPersonalDiffIndices;
		unsigned selectedIndex = QRandomGenerator::global()->bounded(cardPersonalDiffIndices.size());
		visited[cardPersonalDiffIndices[selectedIndex]] = true;
		cardIndices[i] = cardPersonalDiffIndices[selectedIndex];
	}
	m_currentCardIndex = 0;
	m_cardSequence = cardIndices;
	qDebug() << m_cardSequence;
}

void StudySession::nextCard()
{
	m_currentCardIndex++;
	m_answerShowed = false;
}

Card StudySession::getCurrentCard()
{
	return *m_deck->cards()[m_cardSequence[m_currentCardIndex]];
}

void StudySession::saveStatus()
{
	// TODO
}

void StudySession::flipCard()
{
	m_answerShowed = !m_answerShowed;
}

bool StudySession::hasNextCard()
{
    return m_currentCardIndex + 1 < m_cardSequence.length();
}
