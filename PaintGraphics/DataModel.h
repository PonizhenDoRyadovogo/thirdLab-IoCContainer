#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QVector>
#include <QPair>
#include <QString>

struct DataModel {
    QVector<QPair<QString, double>> points;
};

#endif // DATAMODEL_H
