#ifndef ICHARTRENDER_H
#define ICHARTRENDER_H

#include <QtCharts/QChartView>

#include "DataModel.h"

enum ChartType {
    ScatterChart,
    LineChart
};

Q_DECLARE_METATYPE(ChartType)

class IChartRender {
public:
    virtual ~IChartRender() = default;
    virtual ChartType getType() const = 0;
    virtual void render(const DataModel& data, QtCharts::QChartView* view) = 0;
    virtual QString getNameChart() const = 0;
};

#endif // ICHARTRENDER_H
