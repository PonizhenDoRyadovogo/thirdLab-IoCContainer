#include "MainWindow.h"
#include "IocContainer.h"
#include "JsonReader.h"
#include "SqlReader.h"
#include "ScatterChartRender.h"
#include "LineChartRender.h"
#include "ChartFactory.h"
#include "AppConfigurartor.h"

#include <QApplication>

int IOCContainer::s_nextTypeId = 115094801;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<ChartType>("ChartType");

    AppConfigurator cfg;
    cfg.registerReaders<JsonReader, SqlReader>();
    cfg.registerCharts<ScatterChartRender, LineChartRender>();

    auto readerFactory = cfg.container().GetObject<ReaderFactory>();
    auto chartFactory  = cfg.container().GetObject<ChartFactory>();

    MainWindow w(chartFactory, readerFactory);
    w.show();
    return a.exec();
}
