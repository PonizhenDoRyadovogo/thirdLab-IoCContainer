#include "IDataReader.h"

QDateTime IDataReader::parseDate(const QString& raw) const
{
    const auto parts = raw.split(' ', Qt::SkipEmptyParts);
    if(parts.size() != 2) {
        return {};
    }

    const QString datePart = parts[0];
    const QString time = parts[1];

    QDateTime dt = QDateTime::fromString(raw, "dd.MM.yyyy HH:mm");
    if(dt.isValid()) {
        return dt;
    }

    bool ok = false;
    int mins = time.toInt(&ok);
    if(ok) {
        QDate d = QDate::fromString(datePart, "dd.MM.yyyy");
        if(d.isValid()) {
            return d.startOfDay().addSecs(mins * 60);
        }
    }

    return {};
}
