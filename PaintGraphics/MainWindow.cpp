#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

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
    // Создание лэйаута для компоновки настроек
    QHBoxLayout* settingsLayout = new QHBoxLayout();
    settingsLayout->addWidget(labelCharts);
    settingsLayout->addWidget(m_comboBoxCharts);
    settingsLayout->addWidget(labelStyleWin);
    settingsLayout->addWidget(m_comboBoxWindowStyle);
    settingsLayout->addWidget(m_checkBoxBlackAndWhite);
    settingsLayout->addWidget(m_pushButtonSave);
    central->setLayout(settingsLayout);
    setCentralWidget(central);
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

