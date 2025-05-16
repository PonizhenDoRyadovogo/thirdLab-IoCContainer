#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QVector>
#include <QPair>
#include <QDateTime>

struct DataModel {
    QVector<QPair<QDateTime, double>> points;
    bool isEmpty() const {
        return points.empty();
    }
};

#endif // DATAMODEL_H
