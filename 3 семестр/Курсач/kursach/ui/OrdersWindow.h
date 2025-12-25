#ifndef ORDERSWINDOW_H
#define ORDERSWINDOW_H

#include <QDialog>
#include <QTableWidget>
#include <QCalendarWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "../core/Order.h"
#include "../core/OrderList.h"
#include "../core/Vehicle.h"
#include "../core/List.h"
#include "../storage/FileManager.h"

class OrdersWindow : public QDialog {
    Q_OBJECT

public:
    OrdersWindow(OrderList* orders, List<Vehicle*>* vehicles, FileManager* fileManager, QWidget* parent = nullptr);
    ~OrdersWindow();

    void showAddOrderForm();

private slots:
    void onAddOrder();
    void onEditOrder();
    void onDeleteOrder();
    void onCalendarDateChanged();
    void onRefresh();

private:
    void setupUI();
    void refreshOrderTable();
    void showOrderForm(Order* order = nullptr);
    Order* getSelectedOrder();
    bool isVehicleAvailable(int vehicleId, const std::tm& startTime, const std::tm& endTime, int excludeOrderId = -1);

    OrderList* orders;
    List<Vehicle*>* vehicles;
    FileManager* fileManager;

    QTableWidget* orderTable;
    QCalendarWidget* calendar;
    QPushButton* btnAdd;
    QPushButton* btnEdit;
    QPushButton* btnDelete;
    QPushButton* btnRefresh;
};

#endif // ORDERSWINDOW_H

