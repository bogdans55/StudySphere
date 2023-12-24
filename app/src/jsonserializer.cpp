#include <QFile>
#include <QJsonDocument>

#include "lib/jsonserializer.h"

JSONSerializer::JSONSerializer() {}

void JSONSerializer::save(const Serializable &serializable, const QString &filepath, const QString &rootname)
{
	Q_UNUSED(rootname);

	QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
	QFile file(filepath);
	file.open(QFile::WriteOnly);
	file.write(doc.toJson(QJsonDocument::JsonFormat::Indented));
	file.close();
}

QJsonDocument JSONSerializer::createJson(const Serializable &serializable)
{
	QJsonDocument doc = QJsonDocument::fromVariant(serializable.toVariant());
	return doc;
}

void JSONSerializer::loadJson(Serializable &serializable, QJsonDocument &jsonDeck)
{
	serializable.fromVariant(jsonDeck.toVariant());
}

void JSONSerializer::load(Serializable &serializable, const QString &filepath)
{
	QFile file(filepath);
	file.open(QFile::ReadOnly);
	QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
	file.close();
	serializable.fromVariant(doc.toVariant());
}
