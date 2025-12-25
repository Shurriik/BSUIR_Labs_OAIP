#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include "../core/Vehicle.h"
#include "../core/List.h"
#include "../core/OrderList.h"

class StatisticsWindow : public QDialog {
    Q_OBJECT

public:
    StatisticsWindow(List<Vehicle*>* vehicles, OrderList* orders, QWidget* parent = nullptr);
    ~StatisticsWindow();

private:
    void setupUI();
    void calculateStatistics();

    List<Vehicle*>* vehicles;
    OrderList* orders;

    QLabel* totalVehiclesLabel;
    QLabel* onLineLabel;
    QLabel* inParkLabel;
    QLabel* inRepairLabel;
    QLabel* totalOrdersLabel;
    QLabel* needsMaintenanceLabel;
    QTableWidget* statsTable;
};

#endif // STATISTICSWINDOW_H

