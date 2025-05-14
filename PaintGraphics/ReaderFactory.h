#ifndef READERFACTORY_H
#define READERFACTORY_H

#include <QHash>
#include <QVector>
#include <memory>
#include "IDataReader.h"

class ReaderFactory {
public:
    ReaderFactory(const QVector<std::shared_ptr<IDataReader>>& readers){
        for(auto& r: readers) {
            m_map[r->get()] = r;
        }
    }
    std::shared_ptr<IDataReader> getReader(const QString& ext) const {
        return m_map.value(ext.toLower(), nullptr);
    }
private:
    QHash<QString, std::shared_ptr<IDataReader>> m_map;
};

#endif // READERFACTORY_H
