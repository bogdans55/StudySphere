#include "lib/todolist.h"

#include <QVariant>
#include <QVariantMap>
#include <QVariantList>
#include <algorithm>
#include <functional>

ToDoList::ToDoList()
    : m_listToDos()
{}

ToDoList::~ToDoList()
{}

void ToDoList::addToDo(QString text, bool done){
    QPair<QString, bool> pair (text, done);
    m_listToDos.push_back(pair);
}

void ToDoList::deleteToDo(const QString& text) {
    auto it = std::remove_if(m_listToDos.begin(), m_listToDos.end(),
                             [&text](const QPair<QString, bool>& toDo) {
                                 return toDo.first == text;
                             });

    m_listToDos.erase(it, m_listToDos.end());
}

void ToDoList::deleteAllToDos() {
    m_listToDos.clear();
}

QVariant ToDoList::toVariant() const {
    QVariantMap result;

    QVariantList list;
    for (const auto& toDo : m_listToDos) {
        QVariantMap toDoMap;
        toDoMap.insert("text", toDo.first);
        toDoMap.insert("done", toDo.second);

        list.append(toDoMap);
    }

    result.insert("todolist", list);
    return result;
}

void ToDoList::fromVariant(const QVariant& variant) {
    m_listToDos.clear();

    QVariantMap map = variant.toMap();

    QVariantList toDoList = map.value("todolist").toList();

    for (const auto& toDoVariant : toDoList) {
        QVariantMap toDoMap = toDoVariant.toMap();

        QString text = toDoMap.value("text").toString();
        bool done = toDoMap.value("done").toBool();

        QPair<QString, bool> toDoPair(text, done);
        m_listToDos.push_back(toDoPair);
    }
}

