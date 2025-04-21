#include "IoCContainer.h"
#include "Example.h"
#include "Computer.h"

IOCContainer gContainer;

// инициализируем ненулевым числом
int IOCContainer::s_nextTypeId = 115094801;

int main(int argc, const char *argv[])
{
    IOCContainer injector;

    // 1-й способ использования
    std::cout << "===== 1 example =====" << std::endl;
    injector.RegisterInstance<double>(std::make_shared<double>(3.2));
    injector.RegisterInstance<ProcessorType>(std::make_shared<ProcessorType>(x64));
    injector.RegisterInstance<std::string>(std::make_shared<std::string>("v1.2"));
    injector.RegisterFunctor<IProcessor, double, ProcessorType, std::string>(
        std::function<std::shared_ptr<IProcessor>(std::shared_ptr<double>,
        std::shared_ptr<ProcessorType>,
        std::shared_ptr<std::string>)>([] (std::shared_ptr<double> speed,
                                           std::shared_ptr<ProcessorType> type,
                                           std::shared_ptr<std::string> version)->std::shared_ptr<IProcessor>
                                           {
                                               return std::make_shared<IntelProcessor>(*speed, *type, *version);
                                           }));

    injector.RegisterFactory<Computer, Computer, IProcessor>();

    auto pc1 = injector.GetObject<Computer>();
    pc1->configure();

    injector.RegisterFunctor<IProcessor, double, ProcessorType, std::string>(
        std::function<std::shared_ptr<IProcessor>(std::shared_ptr<double>,
        std::shared_ptr<ProcessorType>,
        std::shared_ptr<std::string>)>([] (std::shared_ptr<double> speed,
                                          std::shared_ptr<ProcessorType> type,
                                          std::shared_ptr<std::string> version)->std::shared_ptr<IProcessor>
                                            {
                                                return std::make_shared<AmdProcessor>(*speed, *type, *version);
                                            }));
    pc1->setProcessor(injector);
    pc1->configure();

    // сменим параметры процессора
    injector.RegisterInstance<double>(std::make_shared<double>(2.5));
    injector.RegisterInstance<ProcessorType>(std::make_shared<ProcessorType>(x86));
    injector.RegisterInstance<std::string>(std::make_shared<std::string>("v2.5"));
    pc1->setProcessor(injector);
    pc1->configure();

    // 2-й способ использвания
    std::cout << "===== 2 example =====" << std::endl;
    injector.RegisterInstance<IProcessor>(std::make_shared<IntelProcessor>(4.4, ProcessorType::x64, "v3.1"));
    Computer pc2(injector.GetObject<IProcessor>());
    pc2.configure();

    injector.RegisterInstance<IProcessor>(std::make_shared<AmdProcessor>(2.5, ProcessorType::x86, "v3.1"));
    pc2.setProcessor(injector);
    pc2.configure();

    // 3-й способ использования
    std::cout << "===== 3 example =====" << std::endl;
    injector.RegisterFactory<IProcessor, IntelProcessor, double, ProcessorType, std::string>();
    Computer pc3(injector.GetObject<IProcessor>());
    pc3.configure();

    return 0;
}
