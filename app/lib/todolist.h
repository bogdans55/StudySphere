#ifndef TODOLIST_H
#define TODOLIST_H

#include <QPair>
#include <QVector>

#include "lib/serializable.h"

class ToDoList : public Serializable
{

  public:
	ToDoList();
	~ToDoList();

	QVariant toVariant() const override;
	void fromVariant(const QVariant &variant) override;

	void addToDo(const QString &text, bool isDone);
	void deleteToDo(const QString &text);
	void deleteAllToDos();

	void checkToDo(const QString &text, bool isDone);

	inline QVector<QPair<QString, bool>> toDos() const { return m_listToDos; }

  private:
	QVector<QPair<QString, bool>> m_listToDos;
};

#endif // TODOLIST_H
