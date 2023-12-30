#include "lib/deckpreviewwindow.h"
#include "lib/jsonserializer.h"
#include "lib/servercommunicator.h"
#include "ui_deckpreviewwindow.h"

#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

DeckPreviewWindow::DeckPreviewWindow(QWidget *parent) : QWidget(parent), ui(new Ui::DeckPreviewWindow)
{
	ui->setupUi(this);
}

DeckPreviewWindow::DeckPreviewWindow(Deck *deck, User &user, QWidget *parent)
	: QWidget(parent), ui(new Ui::DeckPreviewWindow), m_user(user), m_deck(*deck)
{
	ui->setupUi(this);
	ui->textEdit_card_preview->setText(deck->cards().at(m_currentCardIndex)->questionText());
}

DeckPreviewWindow::~DeckPreviewWindow()
{
	delete ui;
}

void DeckPreviewWindow::on_pushButton_flip_preview_clicked()
{
	if (m_answerShowed) {
		ui->textEdit_card_preview->setText(m_deck.cards().at(m_currentCardIndex)->questionText());
		ui->label_card_preview->setText(tr("Pitanje"));
	}
	else {
		ui->textEdit_card_preview->setText(m_deck.cards().at(m_currentCardIndex)->questionAnswer());
		ui->label_card_preview->setText(tr("Odgovor"));
	}
	m_answerShowed = !m_answerShowed;
}

void DeckPreviewWindow::on_pushButton_cancel_clicked()
{
	close();
}

void DeckPreviewWindow::on_pushButton_add_clicked()
{
	ServerCommunicator communicator;

	QJsonObject requestObject;

	JSONSerializer serializer;
	QJsonDocument doc = serializer.createJson(m_deck);

	requestObject["action"] = "saveDeck";
	requestObject["username"] = m_user.username();
	requestObject["deck"] = doc.toVariant().toJsonObject();

	QJsonDocument request(requestObject);

	communicator.sendRequest(request);

	QMessageBox::information(this, tr("Uspešno dodat špil"), tr("Izabrani špil je uspešno dodat i sačuvan!"));

	emit sendPublicDeck(m_deck.name() + "_" + QString::number(m_deck.deckId()));

	close();
}

void DeckPreviewWindow::on_pushButton_next_clicked()
{
	if (hasNextCard()) {
		m_currentCardIndex++;
        auto cards = m_deck.cards();
        auto card = cards[m_currentCardIndex];
        ui->textEdit_card_preview->setText(card->questionText());
		m_answerShowed = false;
	}
	else {
		QMessageBox::information(this, tr("Pregled špila"), tr("Špil nema više kartica!"));
	}
}

bool DeckPreviewWindow::hasNextCard()
{
	return m_currentCardIndex + 1 < m_deck.cards().length();
}
