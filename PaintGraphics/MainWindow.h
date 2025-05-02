#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <memory>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    std::unique_ptr<QComboBox> _createComboBoxCharts();
    std::unique_ptr<QComboBox> _createComboBoxStyle();
private:
    std::unique_ptr<QComboBox> m_comboBoxCharts;
    std::unique_ptr<QPushButton> m_pushButtonSave;
    std::unique_ptr<QCheckBox> m_checkBoxBlackAndWhite;
    std::unique_ptr<QComboBox> m_comboBoxWindowStyle;
};
#endif // MAINWINDOW_H
