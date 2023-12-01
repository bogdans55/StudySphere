#include "lib/createdeckwindow.h"
#include "ui_createdeckwindow.h"

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

void CreateDeckWindow::on_finishedButton_clicked()
{
    // TODO save created deck
    close();
}


void CreateDeckWindow::on_addNewButton_clicked()
{
    // TODO add card to deck
    m_questionDifficulty = new QButtonGroup(this);
    m_questionDifficulty->addButton(ui->easyRadioButton, 1);
    m_questionDifficulty->addButton(ui->mediumRadioButton, 2);
    m_questionDifficulty->addButton(ui->hardRadioButton, 3);

    ui->questionTextEdit->clear();
    ui->answerTextEdit->clear();
    // TODO clear radio buttons
}

