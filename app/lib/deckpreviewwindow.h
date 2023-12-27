#ifndef DECKPREVIEWWINDOW_H
#define DECKPREVIEWWINDOW_H

#include <QWidget>

namespace Ui {
class DeckPreviewWindow;
}

class DeckPreviewWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DeckPreviewWindow(QWidget *parent = nullptr);
    ~DeckPreviewWindow();

private:
    Ui::DeckPreviewWindow *ui;
};

#endif // DECKPREVIEWWINDOW_H
