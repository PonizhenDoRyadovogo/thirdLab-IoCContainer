QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT+=charts
QT+=sql
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src\IDataReader.cpp \
    src\JsonReader.cpp \
    src\LineChartRender.cpp \
    src\ScatterChartRender.cpp \
    src\SqlReader.cpp \
    src\main.cpp \
    src\MainWindow.cpp

HEADERS += \
    headers\AppConfigurartor.h \
    headers\ChartFactory.h \
    headers\DataModel.h \
    headers\IChartRender.h \
    headers\IDataReader.h \
    headers\IocContainer.h \
    headers\JsonReader.h \
    headers\LineChartRender.h \
    headers\MainWindow.h \
    headers\ReaderFactory.h \
    headers\ScatterChartRender.h \
    headers\SqlReader.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
