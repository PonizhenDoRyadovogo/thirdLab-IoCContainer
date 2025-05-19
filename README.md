# Оконное приложение по печати графиков по данным временных рядов
## Постановка задачи:
Продумать и релизовать архитектуру программы, которая умеет отрисовывать графики по данным временных рядов. Приложение должно уметь считывать данные с разных файлов (.sql, .json и т.д.), должно уметь орисовывать разные типы графиков, 
уметь менять стиль графика на черно-белый, а также сохранять полученный график в .pdf файл. При этом приложение должно быть легко расширяемым, то есть при добавлении новых типов графиков или новых форматов принимаемых файлов, нам 
не пришлось бы лезть уже в существующий класс
## Реализация
### Inversion of Control (IoC)
- `IOCContainer` регистрирует и создаёт:
  - **ReaderFactory** (JSON, SQLite и др.)
  - **ChartFactory** (LineChart, ScatterChart и др.)
- `AppConfigurator` настраивает контейнер в одном месте.
- `GetObject<ReaderFactory>()` и `GetObject<ChartFactory>()` передаются в `MainWindow`.
### Применение паттерна стратегия
- `ReaderFactory` хранит в себе конкретные стратегии по чтению данных из файлов. Происходит это через указатели на базовый класс стратегий `IReaderData`
- `ChartFactory` хранит в себе конкретные стратегии по отрисовке данных. Происходит это через указатели на базовый класс `IChartrender`
## Доработка IoC container
Нам уже была предложена реализация IoC-контейнера, но для данной работы я его доработал, а именно:
- внедрил функцию, которая регистрирует конкретные ридеры самих на себя, а затем регистрирует `ReaderFactory` с этими зарегистрированными ридерами:
``` c++
  template<typename... ReaderTs>
    void RegisterReaders() {
        // Зарегистрировать каждого Reader-а как сам на себя
        ( RegisterFactory<ReaderTs, ReaderTs>(), ... );

        // Зарегистрировать фабрику по указателю на статическую функцию
        RegisterFunctor<ReaderFactory, ReaderTs...>(
            &IOCContainer::CreateReaderFactoryFn<ReaderTs...>
            );
    }
  ```
- внедрил функцию, которая регистрирует конкретные рендеры самих на себя, а затем регистрирует `ChartFactory` с этими зарегистрированными рендерами:
``` c++
template<typename... RenderTs>
    void RegisterCharts() {
        ( RegisterFactory<RenderTs, RenderTs>(), ... );

        RegisterFunctor<ChartFactory, RenderTs...>(
            &IOCContainer::CreateChartFactoryFn<RenderTs...>
            );
    }
```
- ну а сами эти функии используют статические функции:
``` c++
template<typename... ReaderTs>
    static std::shared_ptr<ReaderFactory> CreateReaderFactoryFn(std::shared_ptr<ReaderTs>... readers) {
        QVector<std::shared_ptr<IDataReader>> v{ readers... };
        return std::make_shared<ReaderFactory>(v);
    }

    template<typename... RenderTs>
    static std::shared_ptr<ChartFactory> CreateChartFactoryFn(std::shared_ptr<RenderTs>... renders) {
        QVector<std::shared_ptr<IChartRender>> v{ renders... };
        return std::make_shared<ChartFactory>(v);
    }
```
## UML-диаграмма
![chartPrinting2](https://github.com/user-attachments/assets/03e89f04-f20a-4ae1-978f-1286532c035c)

## Инструкция по расширению функционала
1. **Новый ридер**: наследоваться от `IDataReader`, реализовать `read()` + `supportedExtensions()`, добавить в `AppConfigurator`:
   ``` c++
   cfg.registerReaders<JsonReader, SqlReader, XmlReader>();
   ```
2. **Новый рендер**: наследоваться от `IChartRender`, реализовать методы, добавить в:
   ``` c++
   cfg.registerCharts<LineChartRender, PieChartRender, BoxPlotRender>();
   ```
3. Перезапустите — новый формат сразу появится в интерфейсе.
