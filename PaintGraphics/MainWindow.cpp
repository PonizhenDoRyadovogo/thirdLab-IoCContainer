#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_comboBoxCharts(_createComboBoxCharts())
    , m_comboBoxWindowStyle(_createComboBoxStyle())
{
    setWindowTitle("Charts print");
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
    // Создание вертикального лэйаута
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(settingsLayout);
    mainLayout->addWidget(splitter);
    // Задаем центральный виджет
    central->setLayout(mainLayout);
    setCentralWidget(central);
    // Инициализация модели файловой системы
    m_fileExplorer = new QFileSystemModel(this);
    m_fileExplorer->setFilter(QDir::Files | QDir::NoDotAndDotDot);// покаываем только файлы, но скрываем специальные . ..
    m_fileExplorer->setRootPath(QDir::homePath());
    m_listView->setRootIndex(m_fileExplorer->index(QDir::homePath()));
    m_listView->setModel(m_fileExplorer);
    m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
}

QComboBox* MainWindow::_createComboBoxCharts() const
{
    QComboBox* comboBox = new QComboBox();
    comboBox->addItem("PieCharts");
    comboBox->addItem("BarCharts");
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

