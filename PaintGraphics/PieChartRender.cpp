#include "PieChartRender.h"

ChartType PieChartRender::getType() const
{
    return ChartType::PieChart;
}

void PieChartRender::render(const DataModel& data, QtCharts::QChartView* view)
{
    QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
    for (auto& p: data.points) {
        series->append(p.first, p.second);
    }
    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Pie chart");
    chart->legend()->setAlignment(Qt::AlignRight);
    view->setChart(chart);
}
