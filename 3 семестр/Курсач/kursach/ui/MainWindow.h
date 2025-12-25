#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QStatusBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include "../core/Vehicle.h"
#include "../core/List.h"
#include "../core/OrderList.h"
#include "../core/HistoryManager.h"
#include "../storage/FileManager.h"

QT_BEGIN_NAMESPACE
class QTabWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddVehicle();
    void onEditVehicle();
    void onDeleteVehicle();
    void onRefreshVehicles();
    void onFilterChanged();
    void onViewOrders();
    void onAddOrder();
    void onViewStatistics();
    void onViewOrdersCalendar();
    void onSaveData();
    void onLoadData();
    void onUndo();
    void onRedo();

private:
    void setupUI();
    void loadVehicles();
    void refreshVehicleTable();
    void showVehicleForm(Vehicle* vehicle = nullptr);
    Vehicle* getSelectedVehicle();
    void showError(const QString& message);
    void showInfo(const QString& message);
    void logOperation(const QString& operation);
    void updateUndoRedoButtons();

    // Компоненты интерфейса
    QTabWidget* tabWidget;
    QTableWidget* vehicleTable;
    QLineEdit* filterBrand;
    QLineEdit* filterModel;
    QComboBox* filterStatus;
    QComboBox* filterType;
    QPushButton* btnAddVehicle;
    QPushButton* btnEditVehicle;
    QPushButton* btnDeleteVehicle;
    QPushButton* btnRefresh;
    QPushButton* btnViewOrders;
    QPushButton* btnAddOrder;
    QPushButton* btnStatistics;
    QPushButton* btnSave;
    QPushButton* btnLoad;
    QPushButton* btnUndo;
    QPushButton* btnRedo;
    QLabel* statusLabel;

    // Данные
    List<Vehicle*> vehicles;
    OrderList orders;
    FileManager fileManager;
    HistoryManager historyManager;
};

#endif // MAINWINDOW_H

