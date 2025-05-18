#ifndef JSONREADER_H
#define JSONREADER_H

#include "IDataReader.h"

class JsonReader : public IDataReader
{
public:
    DataModel read(const QString& path) override;
    QString get() const override;
};

#endif // JSONREADER_H
