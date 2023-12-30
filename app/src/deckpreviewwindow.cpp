#include "../lib/deckpreviewwindow.h"
#include "../lib/jsonserializer.h"
#include "ui_deckpreviewwindow.h"

#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>

DeckPreviewWindow::DeckPreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckPreviewWindow)
{
    ui->setupUi(this);
}

DeckPreviewWindow::DeckPreviewWindow(Deck deck, User& user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckPreviewWindow),
	  m_user(user),
	  m_deck(deck)
{
	ui->setupUi(this);
	ui->textEdit_card_preview->setText(deck.cards()[m_currentCardIndex]->questionText());
}

DeckPreviewWindow::~DeckPreviewWindow()
{
    delete ui;
}

void DeckPreviewWindow::on_pushButton_flip_preview_clicked()
{
	if (m_answerShowed) {
		ui->textEdit_card_preview->setText(m_deck.cards()[m_currentCardIndex]->questionText());
		ui->label_card_preview->setText("Pitanje");
	}
	else {
		ui->textEdit_card_preview->setText(m_deck.cards()[m_currentCardIndex]->questionAnswer());
		ui->label_card_preview->setText("Odgovor");
	}
	m_answerShowed = !m_answerShowed;
}


void DeckPreviewWindow::on_pushButton_cancel_clicked()
{
	close();
}


void DeckPreviewWindow::on_pushButton_add_clicked()
{
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if (socket.waitForConnected()) {
        QJsonObject request;

        JSONSerializer serializer;
        QJsonDocument doc = serializer.createJson(m_deck);

        qDebug() << doc;

        request["action"] = "saveDeck";
        request["username"] = m_user.username();
        request["deck"] = doc.toVariant().toJsonObject();

        qDebug() << request;

        socket.write(QJsonDocument(request).toJson());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();

        QByteArray responseData = socket.readAll();
        QTextStream stream(responseData);

        qDebug() << responseData;

        qDebug() << "Recieved Data:";
        while (!stream.atEnd()) {
            qDebug() << stream.readLine();
        }

        socket.disconnectFromHost();

        QMessageBox::information(this, "Uspešno dodat špil", "Izabrani špil je uspešno dodat i sačuvan!");
        emit sendPublicDeck(m_deck.name() + "_" + QString::number(m_deck.deckId()));
    }
    else {
        qDebug() << "Failed to connect to the server";
    }

    close();
}


void DeckPreviewWindow::on_pushButton_next_clicked()
{
	if(hasNextCard()){
		m_currentCardIndex++;
		ui->textEdit_card_preview->setText(m_deck.cards()[m_currentCardIndex]->questionText());
		m_answerShowed = false;
	}
	else{
		QMessageBox::information(this, "Pregled špila", "Špil nema više kartica!");
	}
}

bool DeckPreviewWindow::hasNextCard()
{
	return m_currentCardIndex + 1 < m_deck.cards().length();
}

