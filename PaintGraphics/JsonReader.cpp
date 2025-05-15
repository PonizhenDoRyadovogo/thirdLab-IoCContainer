#include "JsonReader.h"

DataModel JsonReader::read(const QString& path)
{
    DataModel m;
    m.points.append({"A", 1.0});
    m.points.append({"B", 2.5});
    return m;
}

QString JsonReader::get() const
{
    return "json";
}
