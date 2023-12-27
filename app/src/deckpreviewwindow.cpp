#include "lib/deckpreviewwindow.h"
#include "ui_deckpreviewwindow.h"

DeckPreviewWindow::DeckPreviewWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeckPreviewWindow)
{
    ui->setupUi(this);
}

DeckPreviewWindow::~DeckPreviewWindow()
{
    delete ui;
}
