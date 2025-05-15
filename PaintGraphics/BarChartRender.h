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
    ChartType getType() const override;
    void render(const DataModel& data, QtCharts::QChartView* view) override;
    QString getNameChart() const override {return m_name;}
private:
    QString m_name = "Bar chart";
};

#endif // BARCHARTRENDER_H
