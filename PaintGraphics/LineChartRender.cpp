#include <QDateTimeAxis>

#include "LineChartRender.h"

ChartType LineChartRender::getType() const
{
    return ChartType::LineChart;
}

void LineChartRender::render(const DataModel& data, QtCharts::QChartView* view)
{
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();
    QtCharts::QLineSeries* series = new QtCharts::QLineSeries();
    series->setPen(QPen(QColor(Qt::darkGreen), 1));

    if (!data.isEmpty()) {
        for (const auto &pair : data.points) {
            minY = qMin(minY, pair.second);
            maxY = qMax(maxY, pair.second);
            series->append(pair.first.toMSecsSinceEpoch(), pair.second);
        }
    }

    QtCharts::QChart* chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setAnimationOptions(QtCharts::QChart::NoAnimation);

    QtCharts::QDateTimeAxis* axisX = new QtCharts::QDateTimeAxis();
    axisX->setFormat("dd.MM.yyyy HH:mm");
    axisX->setLabelsAngle(-45);
    // высчитаем количество меток
    int pixelsPerTick = 100;
    int w = view->size().width();
    int count = qMax(2, w / pixelsPerTick);
    axisX->setTickCount(count);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    axisX->setRange(data.points.first().first, data.points.last().first);

    QtCharts::QValueAxis* axisY = new QtCharts::QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->setRange(minY, maxY);

    view->setChart(chart);
}
