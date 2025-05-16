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
        categories << p.first.toString("yyyy-MM-dd HH:mm");
    }
    auto *series = new QtCharts::QBarSeries();
    series->append(set);
    auto *chart = new QtCharts::QChart();
    chart->addSeries(series);

    chart->setTitle("Bar Chart");
    auto *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    //    — ось значений по Y
    auto *axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    view->setChart(chart);
}
