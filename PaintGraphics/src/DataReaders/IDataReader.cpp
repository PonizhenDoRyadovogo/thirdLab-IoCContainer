#include "IDataReader.h"

const QVector<QString> IDataReader::FORMAT_DATE = {"dd.MM.yyyy HH:mm"
    , "dd.MM.yyyy"
    , "yyyy.MM.dd HH:mm"
    , "yyyy.MM.dd"
    , "dd-MM-yyyy HH:mm"
    , "dd-MM-yyy"
    , "yyyy-MM-dd HH:mm"
    , "yyyy-MM-dd"
};

QDateTime IDataReader::parseDate(const QString& raw) const
{
    const auto parts = raw.split(' ', Qt::SkipEmptyParts);
    if(parts.size() != 2) {
        return {};
    }

    const QString datePart = parts[0];
    const QString time = parts[1];

    for(const auto& format: FORMAT_DATE) {
        QDateTime dt = QDateTime::fromString(raw, format);
        if(dt.isValid()) {
            return dt;
        }
    }

    bool ok = false;
    int mins = time.toInt(&ok);
    if(ok) {
        for(const auto& format: FORMAT_DATE) {
            QDate d = QDate::fromString(datePart, format);
            if(d.isValid()) {
                return d.startOfDay().addSecs(mins * 60);
            }
        }
    }

    return {};
}
