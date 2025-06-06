#ifndef IDATAREADER_H
#define IDATAREADER_H

#include "DataModel.h"

class IDataReader
{
public:
    virtual ~IDataReader() = default;
    virtual DataModel read(const QString& path) = 0;
    virtual QString get() const = 0;
    virtual QDateTime parseDate(const QString& raw) const;
private:
    static const QVector<QString> FORMAT_DATE;
};

#endif // IDATAREADER_H
