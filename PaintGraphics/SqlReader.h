#ifndef SQLREADER_H
#define SQLREADER_H

#include "IDataReader.h"

class SqlReader : public IDataReader
{
public:
    DataModel read(const QString& path) override;
    QString get() const override;

};

#endif // SQLREADER_H
