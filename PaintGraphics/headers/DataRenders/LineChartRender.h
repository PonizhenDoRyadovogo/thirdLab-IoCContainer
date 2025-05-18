#ifndef LINECHARTRENDER_H
#define LINECHARTRENDER_H

#include <QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include "IChartRender.h"

class LineChartRender : public IChartRender
{
public:
    ChartType getType() const override;
    void render(const DataModel& data, QtCharts::QChartView* view) override;
    QString getNameChart() const override {return m_name;}
private:
    QString m_name = "Line chart";
};

#endif // LINECHARTRENDER_H
