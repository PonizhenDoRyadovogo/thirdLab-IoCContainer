#ifndef SCATTERCHARTRENDER_H
#define SCATTERCHARTRENDER_H

#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <QValueAxis>

#include "IChartRender.h"

class ScatterChartRender : public IChartRender
{
public:
    ChartType getType() const override;
    void render(const DataModel& data, QtCharts::QChartView* view) override;
    QString getNameChart() const override {return m_name;}
private:
    QString m_name = "Scatter chart";
};

#endif // SCATTERCHARTRENDER_H
