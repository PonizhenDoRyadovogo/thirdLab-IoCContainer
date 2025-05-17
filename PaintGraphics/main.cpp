#include "MainWindow.h"
#include "IocContainer.h"
#include "JsonReader.h"
#include "SqlReader.h"
#include "ScatterChartRender.h"
#include "LineChartRender.h"
#include "ChartFactory.h"

#include <QApplication>

int IOCContainer::s_nextTypeId = 115094801;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IOCContainer injector;
    qRegisterMetaType<ChartType>("ChartType");
    injector.RegisterFactory<JsonReader, JsonReader>();
    injector.RegisterFactory<SqlReader, SqlReader>();
    injector.RegisterFactory<ScatterChartRender, ScatterChartRender>();
    injector.RegisterFactory<LineChartRender, LineChartRender>();

    injector.RegisterFunctor<ReaderFactory, JsonReader, SqlReader>(
        std::function<std::shared_ptr<ReaderFactory>(
            std::shared_ptr<JsonReader>,
            std::shared_ptr<SqlReader>
            )>(
            [](std::shared_ptr<JsonReader> jr,
               std::shared_ptr<SqlReader>   sr)
            {
                QVector<std::shared_ptr<IDataReader>> readers;
                readers.append(jr);
                readers.append(sr);
                return std::make_shared<ReaderFactory>(readers);
            }
            )
        );
    injector.RegisterFunctor<ChartFactory, ScatterChartRender, LineChartRender>(
        std::function<std::shared_ptr<ChartFactory>(
            std::shared_ptr<ScatterChartRender>,
            std::shared_ptr<LineChartRender>
            )>(
            [](std::shared_ptr<ScatterChartRender> pie, std::shared_ptr<LineChartRender> bar)
            {
                QVector<std::shared_ptr<IChartRender>> renderers;
                renderers.append(pie);
                renderers.append(bar);
                return std::make_shared<ChartFactory>(renderers);
            }
            )
        );

    MainWindow w(injector.GetObject<ChartFactory>(), injector.GetObject<ReaderFactory>());
    w.show();
    return a.exec();
}
