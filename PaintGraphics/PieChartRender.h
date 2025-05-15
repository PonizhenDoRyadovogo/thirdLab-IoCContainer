#ifndef PIECHARTRENDER_H
#define PIECHARTRENDER_H

#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

#include "IChartRender.h"

class PieChartRender : public IChartRender
{
public:
    ChartType getType() const override;
    void render(const DataModel& data, QtCharts::QChartView* view) override;
    QString getNameChart() const override {return m_name;}
private:
    QString m_name = "Pie chart";
};

#endif // PIECHARTRENDER_H
