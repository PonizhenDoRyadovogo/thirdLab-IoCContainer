#ifndef CHARTFACTORY_H
#define CHARTFACTORY_H

#include <QHash>
#include "IChartRender.h"

class ChartFactory {
public:
    ChartFactory(const QVector<std::shared_ptr<IChartRender>>& renders) {
        for(auto& r: renders) {
            m_map[r->getType()] = r;
        }
    }
    std::shared_ptr<IChartRender> getRender(ChartType t) const {
        return m_map.value(t, nullptr);
    }
private:
    QHash<ChartType, std::shared_ptr<IChartRender>> m_map;
};

#endif // CHARTFACTORY_H
