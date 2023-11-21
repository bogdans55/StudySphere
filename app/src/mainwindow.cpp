#include "../lib/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_deck = new Deck("name", Privacy::PRIVATE, 5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString qText = ui->lineEdit->text();
    CardContent q(qText);

    QString aText = ui->lineEdit_2->text();
    CardContent a(aText);

    Card *newCard = new Card(q, a, Difficulty::EASY);

    m_deck->addCard(*newCard);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();


    ui->textEdit->append(m_deck->getCards().back().getQuestion().getText()
                         + "\n- "
                         + m_deck->getCards().back().getAnswer().getText() + "\n");
}




