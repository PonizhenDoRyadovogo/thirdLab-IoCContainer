QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT+=charts
QT+=sql
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/headers/DataReaders \
               $$PWD/headers/DataRenders \
               $$PWD/headers \


SOURCES += \
    src/DataReaders/IDataReader.cpp \
    src/DataReaders/JsonReader.cpp \
    src/DataRenders/LineChartRender.cpp \
    src/DataRenders/ScatterChartRender.cpp \
    src/DataReaders/SqlReader.cpp \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    headers/AppConfigurartor.h \
    headers/DataRenders/ChartFactory.h \
    headers/DataModel.h \
    headers/DataRenders/IChartRender.h \
    headers/DataReaders/IDataReader.h \
    headers/IocContainer.h \
    headers/DataReaders/JsonReader.h \
    headers/DataRenders/LineChartRender.h \
    headers/MainWindow.h \
    headers/DataReaders/ReaderFactory.h \
    headers/DataRenders/ScatterChartRender.h \
    headers/DataReaders/SqlReader.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
