#include "BarChartRender.h"

ChartType BarChartRender::getType() const
{
    return ChartType::BarChart;
}

void BarChartRender::render(const DataModel& data, QtCharts::QChartView* view)
{
    auto *set = new QtCharts::QBarSet("Value");
    QStringList categories;
    for (auto &p : data.points) {
        *set << p.second;
        categories << p.first;
    }
    auto *series = new QtCharts::QBarSeries();
    series->append(set);
    auto *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Bar Chart");
    chart->createDefaultAxes();
    view->setChart(chart);
}
