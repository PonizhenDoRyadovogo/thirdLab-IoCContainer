#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFileSystemModel>
#include <QListView>
#include <QtCharts>
#include <memory>
#include <QModelIndex>

#include "ChartFactory.h"
#include "ReaderFactory.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<ChartFactory> chart, std::shared_ptr<ReaderFactory> reader, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onOpenFolderClicked();
    void onFileSelected(const QModelIndex& ix);
    void onChartTypeChanged();
    void onBlackWhiteToggled(bool checked);
    void onSaveButtonClicked();
protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QComboBox* _createComboBoxCharts() const;
    void _setEnableSaveButton();
    void _setEnableCheckBox();
    void _setDisableSaveButton();
    void _setDisableCheckBox();
    void _clearChart();
    void _onBlackWhiteStyle();
private:
    QComboBox* m_comboBoxCharts = nullptr;
    QPushButton* m_pushButtonSave = nullptr;
    QPushButton* m_pushButtonFolder = nullptr;
    QCheckBox* m_checkBoxBlackAndWhite = nullptr;
    QFileSystemModel* m_fileExplorer = nullptr;
    QListView* m_listView = nullptr;
    QtCharts::QChartView* m_chartView = nullptr;
    std::shared_ptr<ReaderFactory> m_readerFactory;
    std::shared_ptr<ChartFactory> m_chartFactory;
    DataModel m_currentData;
};
#endif // MAINWINDOW_H
