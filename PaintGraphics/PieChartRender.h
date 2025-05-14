#ifndef PIECHARTRENDER_H
#define PIECHARTRENDER_H

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

#include "IChartRender.h"

class PieChartRender : public IChartRender
{
public:
    virtual ChartType getType() const override;
    virtual void render(const DataModel& data, QtCharts::QChartView* view) override;
};

#endif // PIECHARTRENDER_H
