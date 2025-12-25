#ifndef ORDERSCALENDARWINDOW_H
#define ORDERSCALENDARWINDOW_H

#include <QDialog>
#include <QCalendarWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QTextCharFormat>
#include "../core/OrderList.h"
#include "../core/List.h"
#include "../core/Vehicle.h"

class OrdersCalendarWindow : public QDialog {
    Q_OBJECT

public:
    OrdersCalendarWindow(OrderList* orders, List<Vehicle*>* vehicles, QWidget* parent = nullptr);
    ~OrdersCalendarWindow() = default;

private slots:
    void onDateSelected(const QDate& date);
    void onOrderDoubleClicked(QListWidgetItem* item);
    void onRefresh();

private:
    void setupUI();
    void updateOrdersList(const QDate& date);
    void highlightDatesWithOrders();
    QString formatOrderInfo(const Order& order);

    OrderList* orders;
    List<Vehicle*>* vehicles;
    
    QCalendarWidget* calendar;
    QListWidget* ordersList;
    QLabel* dateLabel;
    QLabel* ordersCountLabel;
    QPushButton* refreshButton;
    QPushButton* closeButton;
};

#endif // ORDERSCALENDARWINDOW_H

