#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "JsonReader.h"

DataModel JsonReader::read(const QString& path)
{
    DataModel result;
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly)) {
        return {};
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if(doc.isNull()) {
        return {};
    } else if(doc.isArray()) {
        QJsonArray arr = doc.array();
        for(int i = 0; i < arr.size(); ++i) {
            if(arr[i].isObject()) {
                QJsonObject obj = arr[i].toObject();
                QDateTime date;
                double val = 0;
                bool ok = false;
                for(const QJsonValue& value: obj) {
                    if(value.isString()) {
                        date = parseDate(value.toString());
                    } else if(value.isDouble()) {
                        val = value.toDouble();
                        ok = true;
                    }
                    if(date.isValid() && ok) {
                        result.points.append({date, val});
                    }
                }
            }
        }
    }
    return result;
}

QString JsonReader::get() const
{
    return "json";
}
