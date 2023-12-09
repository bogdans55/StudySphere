#include "lib/createdeckwindow.h"
#include "ui_createdeckwindow.h"
#include "lib/card.h"
#include "lib/serializer.h"
#include "lib/jsonserializer.h"
#include <QTcpSocket>
#include <QTcpServer>

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
    return ui->textEdit_question->toPlainText();
}

QString CreateDeckWindow::getAnswerText() const
{
    return ui->textEdit_answer->toPlainText();
}

Difficulty CreateDeckWindow::getDifficulty() const
{
    if(m_questionDifficulty->checkedId() == 1)
        return Difficulty::EASY;
    else if (m_questionDifficulty->checkedId() == 2)
        return Difficulty::MEDIUM;
    else return Difficulty::HARD;
} //default difficulty set to HARD, change if needed

void CreateDeckWindow::on_pushButton_finish_clicked()
{

    // m_deck.toJson();
    JSONSerializer *serializer = new JSONSerializer();
    // serializer->save(m_deck, "../decks/" + m_deck.name() + ".json");

    QJsonDocument doc = serializer ->createJson(m_deck);


    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if(socket.waitForConnected()){
        QJsonObject request;
        request["action"] = "saveDeck";
        request["username"] = "marko1684";
        request["deck"] = doc.toVariant().toJsonObject();

        socket.write(QJsonDocument(request).toJson());
        socket.waitForBytesWritten();
        socket.waitForReadyRead();

        QByteArray responseData = socket.readAll();
        QTextStream stream(responseData);

        qDebug() << "Recieved Data:";
        while (!stream.atEnd()) {
            qDebug() << stream.readLine();
        }

        socket.disconnectFromHost();
    }else{
        qDebug() << "Failed to connect to the server";
    }


    close();
}


void CreateDeckWindow::on_pushButton_add_clicked()
{

    m_questionDifficulty = new QButtonGroup(this);
    m_questionDifficulty->addButton(ui->radioButton_easy, 1);
    m_questionDifficulty->addButton(ui->radioButton_medium, 2);
    m_questionDifficulty->addButton(ui->radioButton_hard, 3);

    QString m_question = getQuestionText();
    QString m_answer = getAnswerText();
    Difficulty m_difficulty = getDifficulty();

    Card m_card (m_question, m_answer, m_difficulty);

    m_deck.addCard(m_card);

    ui->textEdit_question->clear();
    ui->textEdit_answer->clear();
    // TODO clear radio buttons
}

