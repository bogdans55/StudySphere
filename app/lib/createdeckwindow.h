#ifndef CREATEDECKWINDOW_H
#define CREATEDECKWINDOW_H

#include <QWidget>
#include <QString>
#include <QButtonGroup>
#include "deck.h"

namespace Ui {
class CreateDeckWindow;
}

class CreateDeckWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CreateDeckWindow(QWidget *parent = nullptr);

    CreateDeckWindow( QString name, Privacy privacy, QWidget *parent = nullptr);

    ~CreateDeckWindow();

    QString getQuestionText() const;
    QString getAnswerText() const;
    Difficulty getDifficulty() const;




private slots:
    void on_pushButton_finish_clicked();

    void on_pushButton_add_clicked();

private:
    Ui::CreateDeckWindow *ui;
    Deck m_deck;
    QButtonGroup *m_questionDifficulty;
};

#endif // CREATEDECKWINDOW_H
