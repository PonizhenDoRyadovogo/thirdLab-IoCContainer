#include <QtSql>
#include <QMessageBox>

#include "SqlReader.h"

DataModel SqlReader::read(const QString& path)
{
    static QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    DataModel result;
    dbase.setDatabaseName(path);
    if(!dbase.open()) {
        return result;
    }

    auto tables = dbase.tables();
    if(tables.isEmpty()) {
        dbase.close();
        return result;
    }

    QSqlQuery query;
    if(!query.exec("SELECT * FROM " + tables.first())) {
        dbase.close();
        return result;
    } else {
        while(query.next()) {
            QString raw = query.value(0).toString();
            QDateTime dt = parseDate(raw);
            if(!dt.isValid()) {
                continue;
            }
            double val = query.value(1).toDouble();
            result.points.append({dt, val});
        }
    }
    dbase.close();
    return result;
}

QString SqlReader::get() const
{
    return "sqlite";
}
