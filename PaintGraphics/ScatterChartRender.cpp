#include <QtCharts/QChartView>
#include <QtCharts/QDateTimeAxis>

#include "ScatterChartRender.h"

ChartType ScatterChartRender::getType() const
{
    return ChartType::ScatterChart;
}

void ScatterChartRender::render(const DataModel& data, QtCharts::QChartView* view)
{
    QtCharts::QScatterSeries* series = new QtCharts::QScatterSeries();

    int total = data.points.size();
    int maxPixels = view->width() > 0 ? view->width() : 1000;
    int step = qMax(1, total/maxPixels);

    double minY = data.points.first().second;
    double maxY = minY;

    if(!data.isEmpty()) {
        for(int i = 0; i < total; i += step) {
            minY = qMin(minY, data.points[i].second);
            maxY = qMax(maxY, data.points[i].second);
            series->append(data.points[i].first.toMSecsSinceEpoch(), data.points[i].second);
        }
    }

    series->setMarkerSize(5.0);
    series->setPen(QPen(Qt::darkMagenta, 1));
    auto *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setAnimationOptions(QtCharts::QChart::NoAnimation);

    auto *axisX = new QtCharts::QDateTimeAxis();
    axisX->setFormat("dd.MM.yyyy HH:mm");
    axisX->setTickCount(10);
    axisX->setLabelsAngle(-45);
    axisX->setRange(data.points.first().first,
                    data.points.last().first);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QtCharts::QValueAxis();
    axisY->setLabelFormat("%.2f");
    axisY->setRange(minY, maxY);
    axisY->setGridLineVisible(true);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(chart);
}
