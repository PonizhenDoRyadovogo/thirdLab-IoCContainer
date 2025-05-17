#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>

#include "PieChartRender.h"

ChartType PieChartRender::getType() const
{
    return ChartType::PieChart;
}

void PieChartRender::render(const DataModel& data, QtCharts::QChartView* view)
{
    QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
    for (auto& p: data.points) {
        QString tmp = p.first.toString("dd.MM.yyyy HH:mm");
        series->append(tmp, p.second);
    }
    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Pie chart");
    chart->setAnimationOptions(QtCharts::QChart::NoAnimation);
    view->setRenderHint(QPainter::Antialiasing, false);
    chart->legend()->setAlignment(Qt::AlignRight);
    view->setChart(chart);
}
