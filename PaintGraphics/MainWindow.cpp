#include <QGridLayout>
#include <QHBoxLayout>

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_comboBoxCharts(_createComboBoxCharts())
    , m_comboBoxWindowStyle(_createComboBoxStyle())
{
    setWindowTitle("Charts print");
    m_pushButtonSave = std::make_unique<QPushButton>("Save", this);
    m_checkBoxBlackAndWhite = std::make_unique<QCheckBox>("Black and white", this);
    std::unique_ptr<QGridLayout> baseLayout = std::make_unique<QGridLayout>();
    std::unique_ptr<QHBoxLayout> settingsLayout = std::make_unique<QHBoxLayout>(this);
    settingsLayout->addWidget(m_pushButtonSave.get());
    settingsLayout->addWidget(m_checkBoxBlackAndWhite.get());
    //settingsLayout->addWidget(m_comboBoxCharts.get());
    //settingsLayout->addWidget(m_comboBoxWindowStyle.get());
    //settingsLayout->addStretch();
    //baseLayout->addLayout(settingsLayout.get(), 0, 0, 1, 3);
}

std::unique_ptr<QComboBox> MainWindow::_createComboBoxCharts()
{
    std::unique_ptr<QComboBox> comboBox = std::make_unique<QComboBox>(this);
    comboBox->addItem("PieCharts");
    comboBox->addItem("BarCharts");
    return comboBox;
}

std::unique_ptr<QComboBox> MainWindow::_createComboBoxStyle()
{
    std::unique_ptr<QComboBox> comboBox = std::make_unique<QComboBox>(this);
    comboBox->addItem("Light");
    comboBox->addItem("Dark");
    return comboBox;
}

MainWindow::~MainWindow()
{
}

