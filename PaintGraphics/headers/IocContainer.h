#ifndef IOCCONTAINER_H
#define IOCCONTAINER_H
#include <functional>
#include <memory>
#include <map>

#include "ChartFactory.h"
#include "ReaderFactory.h"

class IOCContainer
{
    static int s_nextTypeId;
    template<typename T>
    static int GetTypeID() {
        static int typeId = s_nextTypeId++;
        return typeId;
    }

public:
    class FactoryRoot
    {
    public:
        virtual ~FactoryRoot() {}
    };


    std::map<int, std::shared_ptr<FactoryRoot>> m_factories;

    //Получить экземпляр объекта
    template<typename T>
    class CFactory : public FactoryRoot
    {
        std::function<std::shared_ptr<T>()> m_functor;

    public:
        ~CFactory() {}

        CFactory(std::function<std::shared_ptr<T>()> functor)
            : m_functor(functor)
        {}

        std::shared_ptr<T> GetObject() {
            return m_functor();
        }
    };

    template<typename T>
    std::shared_ptr<T> GetObject() {
        auto typeId = GetTypeID<T>();
        auto factoryBase = m_factories[typeId];
        auto factory = std::static_pointer_cast<CFactory<T>>(factoryBase);
        return factory->GetObject();
    }

    //Регистрация экземпляров

    //Самая простая реализация - зарегистрировать функтор
    template<typename TInterface, typename... TS>
    void RegisterFunctor(
        std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)> functor) {
        m_factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
            [ = ] { return functor(GetObject<TS>()...); });
    }

    //Регистрация одного экземпляра объекта
    template<typename TInterface>
    void RegisterInstance(std::shared_ptr<TInterface> t) {
        m_factories[GetTypeID<TInterface>()] = std::make_shared<CFactory<TInterface>>(
            [ = ] { return t; });
    }

    //Подаем указатель на функцию
    template<typename TInterface, typename... TS>
    void RegisterFunctor(std::shared_ptr<TInterface> (*functor)(std::shared_ptr<TS>... ts)) {
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS>... ts)>(functor));
    }

    //Фабрика, которая будет вызывать конструктор, для каждого экземпляра
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void RegisterFactory() {
        RegisterFunctor(
            std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments>... ts)>(
                [](std::shared_ptr<TArguments>... arguments) -> std::shared_ptr<TInterface> {
                    return std::make_shared<TConcrete>(
                        std::forward<std::shared_ptr<TArguments>>(arguments)...);
                }));
    }

    //Фабрика, которая будет возвращать один экземпляр
    template<typename TInterface, typename TConcrete, typename... TArguments>
    void RegisterInstance() {
        RegisterInstance<TInterface>(std::make_shared<TConcrete>(GetObject<TArguments>()...));
    }

    template<typename... ReaderTs>
    void RegisterReaders() {
        // Зарегистрировать каждого Reader-а как сам на себя
        ( RegisterFactory<ReaderTs, ReaderTs>(), ... );

        // Зарегистрировать фабрику по указателю на статическую функцию
        RegisterFunctor<ReaderFactory, ReaderTs...>(
            &IOCContainer::CreateReaderFactoryFn<ReaderTs...>
            );
    }

    template<typename... RenderTs>
    void RegisterCharts() {
        ( RegisterFactory<RenderTs, RenderTs>(), ... );

        RegisterFunctor<ChartFactory, RenderTs...>(
            &IOCContainer::CreateChartFactoryFn<RenderTs...>
            );
    }
private:
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
};
#endif // IOCCONTAINER_H
