#ifndef ICHARTRENDER_H
#define ICHARTRENDER_H

#include <QtCharts/QChartView>

#include "DataModel.h"

enum ChartType {
    PieChart,
    BarChart
};

class IChartRender {
public:
    virtual ~IChartRender() = default;
    virtual ChartType getType() const = 0;
    virtual void render(const DataModel& data, QtCharts::QChartView* view) = 0;
};

#endif // ICHARTRENDER_H
