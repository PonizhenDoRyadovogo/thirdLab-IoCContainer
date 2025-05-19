#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSplitter>
#include <QVariant>
#include <QMessageBox>

#include "MainWindow.h"

MainWindow::MainWindow(std::shared_ptr<ChartFactory> chart, std::shared_ptr<ReaderFactory> reader, QWidget *parent)
    : QMainWindow(parent)
    , m_readerFactory(std::move(reader))
    , m_chartFactory(std::move(chart))
{
    setWindowTitle("Charts print");
    setMinimumSize(800, 600);
    // создаем комбо-боксы
    m_comboBoxCharts = _createComboBoxCharts();
    // Создание центрального виджета
    QWidget* central = new QWidget(this);
    // Создание подписей
    QLabel* labelCharts = new QLabel("Choose charts:", central);
    // Инициализация кнопки печати и чекбокса для черно-белого графика
    m_pushButtonSave = new QPushButton("Save chart", central);
    m_pushButtonSave->setEnabled(false);
    m_checkBoxBlackAndWhite = new QCheckBox("Black and white", central);
    m_checkBoxBlackAndWhite->setEnabled(false);
    // Инициализация кнопки для открытия папки
    m_pushButtonFolder = new QPushButton("Open folder", central);
    // Создание лэйаутов для компоновки настроек
    QHBoxLayout* settingsLayout = new QHBoxLayout();
    QHBoxLayout* chartsLayout = new QHBoxLayout(); // эти два лэйаута необходимы для того, чтобы
    // надписи "прилипали" к своим комбо-боксам
    chartsLayout->setSpacing(5);
    chartsLayout->setContentsMargins(0, 0, 0, 0);
    settingsLayout->addWidget(m_pushButtonFolder);
    chartsLayout->addWidget(labelCharts, 0);
    chartsLayout->addWidget(m_comboBoxCharts, 1);
    settingsLayout->addLayout(chartsLayout);
    settingsLayout->addWidget(m_checkBoxBlackAndWhite);
    settingsLayout->addWidget(m_pushButtonSave);
    // Создание области отображения файлов и области отображения графиков, между ними сплиттер
    m_listView = new QListView(this);
    m_chartView = new QtCharts::QChartView(this);
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
    m_listView->setModel(m_fileExplorer);
    m_listView->setRootIndex(m_fileExplorer->index(QDir::homePath()));
    statusBar()->showMessage("Current dir: " + QDir::homePath());
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
    connect(m_pushButtonFolder, &QPushButton::clicked, this, &MainWindow::onOpenFolderClicked);
    // сигнал выбора элемента в списке
    connect(m_listView, &QListView::clicked, this, &MainWindow::onFileSelected);
    // сигнал изменения чарта
    connect(m_comboBoxCharts, &QComboBox::currentTextChanged, this, &MainWindow::onChartTypeChanged);
    // сигнал по включению черно-белого стиля графика
    connect(m_checkBoxBlackAndWhite, &QCheckBox::toggled, this, &MainWindow::onBlackWhiteToggled);
    connect(m_pushButtonSave, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
}

void MainWindow::onOpenFolderClicked()
{
    QFileDialog dlg(this, "Choose folder");
    dlg.setFileMode(QFileDialog::Directory);
    dlg.setOption(QFileDialog::ShowDirsOnly, false);
    dlg.setOption(QFileDialog::DontUseNativeDialog); // используется qt-ная реализация окна, а не windows
    if (dlg.exec() != QDialog::Accepted) {
        return;
    }
    const QStringList files = dlg.selectedFiles();
    const QString dir = files.first();
    if (dir.isEmpty()) {
        return;
    }
    m_fileExplorer->setRootPath(dir);
    m_listView->setRootIndex(m_fileExplorer->index(dir));
    statusBar()->showMessage("Current dir: " + dir);
}

void MainWindow::onFileSelected(const QModelIndex& ix)
{
    QString path = m_fileExplorer->filePath(ix);
    QString ext  = QFileInfo(path).suffix();
    auto reader = m_readerFactory->getReader(ext);
    if (!reader) {
        return;
    }
    m_currentData = reader->read(path);
    if(m_currentData.isEmpty()) {
        _clearChart();
        QMessageBox::warning(this, "Error", "Ooops... Something went wrong. Try again!");
        _setDisableCheckBox();
        _setDisableSaveButton();
        return;
    }
    auto renderer = m_chartFactory->getRender(
        m_comboBoxCharts->currentData().value<ChartType>());
    if (!renderer) {
        QMessageBox::warning(this, "Error", "Ooops... Something went wrong. Try again!");
        _setDisableCheckBox();
        _setDisableSaveButton();
        return;
    }
    renderer->render(m_currentData, m_chartView);
    if(m_checkBoxBlackAndWhite->isChecked()) {
        _onBlackWhiteStyle();
    }
    _setEnableCheckBox();
    _setEnableSaveButton();
}

void MainWindow::onChartTypeChanged()
{
    if (m_currentData.isEmpty()) {
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
    if(m_checkBoxBlackAndWhite->isChecked()) {
        _onBlackWhiteStyle();
    }
}

void MainWindow::onBlackWhiteToggled(bool checked)
{
    if (m_chartView->chart()) {
        if (checked) {
            _onBlackWhiteStyle();
        } else {
            // перерисовываем с нуля
            ChartType type = m_comboBoxCharts->currentData().value<ChartType>();
            auto renderer = m_chartFactory->getRender(type);
            renderer->render(m_currentData, m_chartView);
        }
    }
}

void MainWindow::onSaveButtonClicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save to...", "", "PDF (*.pdf)");
    if (!filePath.isEmpty())
    {
        QPdfWriter pdfWriter(filePath); // Создание средства записи PDF
        QPainter painter(&pdfWriter); // Создание объекта для рисования
        m_chartView->render(&painter); // Рисование диаграммы в pdf
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    if (m_currentData.isEmpty()) {
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
    if(m_checkBoxBlackAndWhite->isChecked()) {
        _onBlackWhiteStyle();
    }
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

void MainWindow::_setEnableSaveButton()
{
    if(!m_pushButtonSave->isEnabled()) {
        m_pushButtonSave->setEnabled(true);
    } else {
        return;
    }
}

void MainWindow::_setEnableCheckBox()
{
    if(!m_checkBoxBlackAndWhite->isEnabled()) {
        m_checkBoxBlackAndWhite->setEnabled(true);
    } else {
        return;
    }
}

void MainWindow::_setDisableSaveButton()
{
    if(m_pushButtonSave->isEnabled()) {
        m_pushButtonSave->setEnabled(false);
    } else {
        return;
    }
}

void MainWindow::_setDisableCheckBox()
{
    if(m_checkBoxBlackAndWhite->isEnabled()) {
        m_checkBoxBlackAndWhite->setEnabled(false);
    } else {
        return;
    }
}

void MainWindow::_clearChart()
{
    if (auto *chart = m_chartView->chart()) {
        chart->removeAllSeries();
        const auto axes = chart->axes();
        for (auto *axis : axes) {
            chart->removeAxis(axis);
        }
        chart->setTitle({});
    }
}

void MainWindow::_onBlackWhiteStyle()
{
    m_chartView->chart()->setTheme(QtCharts::QChart::ChartThemeHighContrast);
    if (auto *axisX = m_chartView->chart()->axes(Qt::Horizontal).value(0)) {
        axisX->setShadesVisible(false);
    }
    if (auto *axisY = m_chartView->chart()->axes(Qt::Vertical).value(0)) {
        axisY->setShadesVisible(false);
    }
}

MainWindow::~MainWindow()
{
}

