#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "IoCContainer.h"

enum ProcessorType
{
    x86,
    x64
};

class IProcessor {
public:
    virtual ~IProcessor() = default;
    virtual std::string getProcessorInfo() const = 0;
public:
    static const std::string PROCESSOR_TYPE[];
};

const std::string IProcessor::PROCESSOR_TYPE[] = {"x86", "x64"};

class IntelProcessor : public IProcessor {
public:
    IntelProcessor(double speed, ProcessorType& type, const std::string& version)
        :m_speed(speed), m_type(type), m_version(version)
    {}
    std::string getProcessorInfo() const override
    {
        return "Intel processor for: " + std::to_string(m_speed) + ", " + m_version + ", " + PROCESSOR_TYPE[m_type];
    }
private:
    double m_speed;
    ProcessorType m_type;
    std::string m_version;
};


class AmdProcessor : public IProcessor {
public:
    AmdProcessor(double speed, ProcessorType& type, const std::string& version)
        :m_speed(speed), m_type(type), m_version(version)
    {}

    std::string getProcessorInfo() const override
    {
        return "AMD processor for: " + std::to_string(m_speed) + ", " + m_version + ", " + PROCESSOR_TYPE[m_type];
    }
private:
    double m_speed;
    ProcessorType m_type;
    std::string m_version;
};

class Computer {
public:
    Computer(std::shared_ptr<IProcessor> p)
        : m_processor(p)
    {}
    void setProcessor(IOCContainer& serviceLocator)
    {
        m_processor = serviceLocator.GetObject<IProcessor>();
    }
    void configure() const
    {
        std::cout << m_processor->getProcessorInfo() << std::endl;
    }
private:
    std::shared_ptr<IProcessor> m_processor;
};

#endif // COMPUTER_H
