#ifndef DECKPREVIEWWINDOW_H
#define DECKPREVIEWWINDOW_H

#include "lib/deck.h"
#include <QWidget>

namespace Ui {
class DeckPreviewWindow;
}

class DeckPreviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DeckPreviewWindow(QWidget *parent = nullptr);
    DeckPreviewWindow(Deck deck, QWidget *parent = nullptr);
    ~DeckPreviewWindow();

private slots:
    void on_pushButton_flip_preview_clicked();

    void on_pushButton_cancel_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_next_clicked();

private:
    Ui::DeckPreviewWindow *ui;

    Deck m_deck;
};

#endif // DECKPREVIEWWINDOW_H
