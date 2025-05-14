#ifndef BARCHARTRENDER_H
#define BARCHARTRENDER_H

#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include "IChartRender.h"

class BarChartRender : public IChartRender
{
public:
    virtual ChartType getType() const override;
    virtual void render(const DataModel& data, QtCharts::QChartView* view) override;
};

#endif // BARCHARTRENDER_H
