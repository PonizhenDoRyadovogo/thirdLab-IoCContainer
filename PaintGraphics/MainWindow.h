#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFileSystemModel>
#include <QListView>
#include <QtCharts>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QComboBox* _createComboBoxCharts() const;
    QComboBox* _createComboBoxStyle() const;
private:
    QComboBox* m_comboBoxCharts = nullptr;
    QPushButton* m_pushButtonSave = nullptr;
    QPushButton* m_pushButtonFolder = nullptr;
    QCheckBox* m_checkBoxBlackAndWhite = nullptr;
    QComboBox* m_comboBoxWindowStyle = nullptr;
    QFileSystemModel* m_fileExplorer = nullptr;
    QListView* m_listView = nullptr;
    QtCharts::QChartView* m_chartView = nullptr;
};
#endif // MAINWINDOW_H
