#include "MainWindow.h"
#include "IocContainer.h"
#include "JsonReader.h"
#include "SqlReader.h"
#include "PieChartRender.h"
#include "BarChartRender.h"
#include "ChartFactory.h"

#include <QApplication>

int IOCContainer::s_nextTypeId = 115094801;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IOCContainer injector;
    injector.RegisterFactory<JsonReader, JsonReader>();
    injector.RegisterFactory<SqlReader, SqlReader>();
    injector.RegisterFunctor<ReaderFactory, JsonReader, SqlReader>(
        std::function<std::shared_ptr<ReaderFactory>(
            std::shared_ptr<JsonReader>, std::shared_ptr<SqlReader>
            )>(
            [](auto jr, auto sr) {
                return std::make_shared<ReaderFactory>(
                    QVector<std::shared_ptr<IDataReader>>{ jr, sr }
                    );
            }
            ));
    injector.RegisterFactory<PieChartRender, PieChartRender>();
    injector.RegisterFactory<BarChartRender, BarChartRender>();
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
    injector.RegisterFunctor<ChartFactory, PieChartRender, BarChartRender>(
        std::function<std::shared_ptr<ChartFactory>(
            std::shared_ptr<PieChartRender>,
            std::shared_ptr<BarChartRender>
            )>(
            [](std::shared_ptr<PieChartRender> pie, std::shared_ptr<BarChartRender> bar)
            {
                QVector<std::shared_ptr<IChartRender>> renderers;
                renderers.append(pie);
                renderers.append(bar);
                return std::make_shared<ChartFactory>(renderers);
            }
            )
        );

    MainWindow w(injector.GetObjectW<ChartFactory>(), injector.GetObjectW<ReaderFactory>());
    w.show();
    return a.exec();
}
