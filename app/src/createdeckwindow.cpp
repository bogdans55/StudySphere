#include "lib/createdeckwindow.h"
#include "ui_createdeckwindow.h"
#include "lib/card.h"
#include "lib/serializer.h"
#include "lib/jsonserializer.h"

CreateDeckWindow::CreateDeckWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDeckWindow)
{
    ui->setupUi(this);
}

CreateDeckWindow::CreateDeckWindow(QString name, Privacy privacy, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDeckWindow),
    m_deck(name, privacy)
{
    ui->setupUi(this);
}

CreateDeckWindow::~CreateDeckWindow()
{
    delete ui;
}

QString CreateDeckWindow::getQuestionText() const
{
    return ui->questionTextEdit->toPlainText();
}

QString CreateDeckWindow::getAnswerText() const
{
    return ui->answerTextEdit->toPlainText();
}

Difficulty CreateDeckWindow::getDifficulty() const
{
    if(m_questionDifficulty->checkedId() == 1)
        return Difficulty::EASY;
    else if (m_questionDifficulty->checkedId() == 2)
        return Difficulty::MEDIUM;
    else return Difficulty::HARD;
} //default difficulty set to HARD, change if needed

void CreateDeckWindow::on_finishedButton_clicked()
{

    // m_deck.toJson();
    JSONSerializer *serializer = new JSONSerializer();
    serializer->save(m_deck, "../decks/" + m_deck.name() + ".json");
    close();
}


void CreateDeckWindow::on_addNewButton_clicked()
{

    m_questionDifficulty = new QButtonGroup(this);
    m_questionDifficulty->addButton(ui->easyRadioButton, 1);
    m_questionDifficulty->addButton(ui->mediumRadioButton, 2);
    m_questionDifficulty->addButton(ui->hardRadioButton, 3);

    QString m_question = getQuestionText();
    QString m_answer = getAnswerText();
    Difficulty m_difficulty = getDifficulty();

    Card m_card (m_question, m_answer, m_difficulty);

    m_deck.addCard(m_card);

    ui->questionTextEdit->clear();
    ui->answerTextEdit->clear();
    // TODO clear radio buttons
}

