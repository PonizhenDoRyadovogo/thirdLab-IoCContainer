#include "JsonReader.h"

DataModel JsonReader::read(const QString& path)
{
    DataModel m;
    QDate d1(2000, 05, 25);
    QDate d2(2004, 05, 01);
    m.points.append({QDateTime(d1.startOfDay()), 1.0});
    m.points.append({QDateTime(d2.startOfDay()), 2.5});
    return m;
}

QString JsonReader::get() const
{
    return "json";
}
