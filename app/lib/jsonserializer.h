#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "serializer.h"
#include <QString>
#include <QJsonDocument>

class JSONSerializer : public Serializer
{
public:
    JSONSerializer();

    void save(const Serializable &serializable, const QString &filepath, const QString &rootname = "") override;
    void load(Serializable &serializable, const QString &filepath) override;
    QJsonDocument createJson(const Serializable& serializable);
    void loadJson(Serializable& serializable, QJsonDocument& jsonDeck);

};

#endif // JSONSERIALIZER_H
