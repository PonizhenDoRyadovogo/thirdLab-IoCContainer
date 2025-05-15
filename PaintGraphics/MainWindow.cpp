#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QVariant>

#include "MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<ChartFactory> chart, std::shared_ptr<ReaderFactory> reader, QWidget *parent)
    : QMainWindow(parent)
    , m_readerFactory(std::move(reader))
    , m_chartFactory(std::move(chart))
{
    setWindowTitle("Charts print");
    m_comboBoxCharts = _createComboBoxCharts();
    m_comboBoxWindowStyle = _createComboBoxStyle();
    // Создание центрального виджета
    QWidget* central = new QWidget(this);
    // Создание подписей
    QLabel* labelCharts = new QLabel("Choose charts:", central);
    QLabel* labelStyleWin = new QLabel("Change the theme:", central);
    // Инициализация кнопки печати и чекбокса для черно-белого графика
    m_pushButtonSave = new QPushButton("Save chart", central);
    m_checkBoxBlackAndWhite = new QCheckBox("Black and white", central);
    // Инициализация кнопки для открытия папки
    m_pushButtonFolder = new QPushButton("Open folder", central);
    // Создание лэйаутов для компоновки настроек
    QHBoxLayout* settingsLayout = new QHBoxLayout();
    QHBoxLayout* chartsLayout = new QHBoxLayout(); // эти два лэйаута необходимы для того, чтобы
    // надписи "прилипали" к своим комбо-боксам
    QHBoxLayout* styleLayout = new QHBoxLayout();
    styleLayout->setContentsMargins(0,0,0,0);
    styleLayout->setSpacing(5);
    chartsLayout->setSpacing(5);
    chartsLayout->setContentsMargins(0, 0, 0, 0);
    settingsLayout->addWidget(m_pushButtonFolder);
    chartsLayout->addWidget(labelCharts, 0);
    chartsLayout->addWidget(m_comboBoxCharts, 1);
    styleLayout->addWidget(labelStyleWin, 0);
    styleLayout->addWidget(m_comboBoxWindowStyle, 1);
    settingsLayout->addLayout(styleLayout);
    settingsLayout->addLayout(chartsLayout);
    settingsLayout->addWidget(m_checkBoxBlackAndWhite);
    settingsLayout->addWidget(m_pushButtonSave);
    // Создание области отображения файлов и области отображения графиков, между ними сплиттер
    m_listView = new QListView();
    m_chartView = new QtCharts::QChartView();
    QSplitter* splitter = new QSplitter(central);
    splitter->addWidget(m_listView);
    splitter->addWidget(m_chartView);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    // Создание вертикального лэйаута
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(settingsLayout);
    mainLayout->addWidget(splitter);
    // Задаем центральный виджет
    central->setLayout(mainLayout);
    setCentralWidget(central);
    // Инициализация модели файловой системы
    m_fileExplorer = new QFileSystemModel(this);
    m_fileExplorer->setFilter(QDir::Files | QDir::NoDotAndDotDot);// показываем только файлы, но скрываем специальные . ..
    m_fileExplorer->setRootPath(QDir::homePath());
    m_listView->setRootIndex(m_fileExplorer->index(QDir::homePath()));
    m_listView->setModel(m_fileExplorer);
    m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
    // выставляем фильтры для файлов
    QStringList filters;
    for(int i = 0; i < m_readerFactory->getExpansions().size(); ++i) {
        filters << "*." + m_readerFactory->getExpansions()[i];
    }
    m_fileExplorer->setNameFilters(filters);
    m_fileExplorer->setNameFilterDisables(false);
    // сигналы
    // сигнал открытия папки по нажатию на кнопку "Open folder"
    connect(m_pushButtonFolder, &QPushButton::clicked, this, [this](){
        QString dir = QFileDialog::getExistingDirectory(this,"Choose folder");
        if (dir.isEmpty()) {
            return;
        }
        m_fileExplorer->setRootPath(dir);
        m_listView->setRootIndex(m_fileExplorer->index(dir));
    });
    // сигнал выбора элемента в списке
    connect(m_listView, &QListView::clicked, this, [&](const QModelIndex &ix){
        QString path = m_fileExplorer->filePath(ix);
        QString ext  = QFileInfo(path).suffix();
        auto reader = m_readerFactory->getReader(ext);
        if (!reader) {
            return;
        }
        m_currentData = reader->read(path);
        auto renderer = m_chartFactory->getRender(
            static_cast<ChartType>(m_comboBoxCharts->currentIndex())
            );
        if (!renderer) {
            return;
        }
        renderer->render(m_currentData, m_chartView);
    });
    // сигнал изменения чарта
    connect(m_comboBoxCharts, &QComboBox::currentTextChanged, this, [this](){
        if (m_currentData.points.isEmpty()) {
            return;
        }
        QVariant v = m_comboBoxCharts->currentData();
        ChartType type = v.value<ChartType>();
        auto renderer = m_chartFactory->getRender(type);
        if (!renderer) {
            return;
        }
        // перерисовываем график
        renderer->render(m_currentData, m_chartView);
    });

}

QComboBox* MainWindow::_createComboBoxCharts() const
{
    QComboBox* comboBox = new QComboBox();
    QVector<std::shared_ptr<IChartRender>> renderers = m_chartFactory->renderers();
    for(auto& r: renderers) {
        comboBox->addItem(r->getNameChart(), QVariant::fromValue(r->getType()));
    }
    return comboBox;
}

QComboBox* MainWindow::_createComboBoxStyle() const
{
    QComboBox* comboBox = new QComboBox();
    comboBox->addItem("Light");
    comboBox->addItem("Dark");
    return comboBox;
}

MainWindow::~MainWindow()
{
}

