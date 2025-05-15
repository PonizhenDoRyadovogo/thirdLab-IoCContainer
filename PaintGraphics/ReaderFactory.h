#ifndef READERFACTORY_H
#define READERFACTORY_H

#include <QHash>
#include <QVector>
#include <QStringList>
#include <memory>
#include "IDataReader.h"

class ReaderFactory {
public:
    ReaderFactory(const QVector<std::shared_ptr<IDataReader>>& readers) {
        for(auto& r: readers) {
            m_map[r->get()] = r;
            m_expansions.append(r->get());
        }
        m_expansions.removeDuplicates();
    }
    std::shared_ptr<IDataReader> getReader(const QString& ext) const {
        return m_map.value(ext.toLower(), nullptr);
    }
    QStringList getExpansions() const {
        return m_expansions;
    }
private:
    QHash<QString, std::shared_ptr<IDataReader>> m_map;
    QStringList m_expansions;
};

#endif // READERFACTORY_H
