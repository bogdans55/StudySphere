#include "lib/deckpreviewwindow.h"
#include "ui_deckpreviewwindow.h"

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
    // TODO
}


void DeckPreviewWindow::on_pushButton_next_clicked()
{
	m_currentCardIndex++;
	m_answerShowed = false;
}

bool DeckPreviewWindow::hasNextCard()
{
	return m_currentCardIndex + 1 < m_deck.cards().length();
}

