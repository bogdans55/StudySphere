#include "lib/deckpreviewwindow.h"
#include "ui_deckpreviewwindow.h"

DeckPreviewWindow::DeckPreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckPreviewWindow)
{
    ui->setupUi(this);
}

DeckPreviewWindow::DeckPreviewWindow(Deck deck, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckPreviewWindow),
    m_deck(deck)
{

}

DeckPreviewWindow::~DeckPreviewWindow()
{
    delete ui;
}

void DeckPreviewWindow::on_pushButton_flip_preview_clicked()
{
	m_answerShowed = !m_answerShowed;
}


void DeckPreviewWindow::on_pushButton_cancel_clicked()
{
    // TODO
}


void DeckPreviewWindow::on_pushButton_add_clicked()
{
    // TODO
}


void DeckPreviewWindow::on_pushButton_next_clicked()
{
    // TODO
}

bool DeckPreviewWindow::hasNextCard()
{
	return m_currentCardIndex + 1 < m_cardSequence.length();
}

