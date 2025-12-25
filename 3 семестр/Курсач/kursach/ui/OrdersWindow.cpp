#include "OrdersWindow.h"
#include "OrderForm.h"
#include "../exceptions/TaxiParkException.h"
#include <QMessageBox>
#include <QHeaderView>
#include <ctime>

// Вспомогательная функция для сравнения структур tm
static bool tmLess(const std::tm& a, const std::tm& b) {
    if (a.tm_year != b.tm_year) return a.tm_year < b.tm_year;
    if (a.tm_mon != b.tm_mon) return a.tm_mon < b.tm_mon;
    if (a.tm_mday != b.tm_mday) return a.tm_mday < b.tm_mday;
    if (a.tm_hour != b.tm_hour) return a.tm_hour < b.tm_hour;
    return a.tm_min < b.tm_min;
}

static bool tmGreater(const std::tm& a, const std::tm& b) {
    return tmLess(b, a);
}

OrdersWindow::OrdersWindow(OrderList* orders, List<Vehicle*>* vehicles, FileManager* fileManager, QWidget* parent)
    : QDialog(parent), orders(orders), vehicles(vehicles), fileManager(fileManager) {
    setupUI();
    refreshOrderTable();
}

OrdersWindow::~OrdersWindow() {
}

void OrdersWindow::setupUI() {
    setWindowTitle("Управление заказами");
    setMinimumSize(900, 600);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Левая сторона - календарь
    QVBoxLayout* leftLayout = new QVBoxLayout();
    calendar = new QCalendarWidget(this);
    connect(calendar, &QCalendarWidget::selectionChanged, this, &OrdersWindow::onCalendarDateChanged);
    leftLayout->addWidget(calendar);
    mainLayout->addLayout(leftLayout, 1);

    // Правая сторона - таблица и кнопки
    QVBoxLayout* rightLayout = new QVBoxLayout();

    orderTable = new QTableWidget(this);
    orderTable->setColumnCount(7);
    orderTable->setHorizontalHeaderLabels({"ID", "Автомобиль ID", "Клиент", "Телефон", 
                                          "Откуда", "Куда", "Дата/Время"});
    orderTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    orderTable->setSelectionMode(QAbstractItemView::SingleSelection);
    orderTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    orderTable->horizontalHeader()->setStretchLastSection(true);
    rightLayout->addWidget(orderTable);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    btnAdd = new QPushButton("Добавить заказ", this);
    btnEdit = new QPushButton("Редактировать", this);
    btnDelete = new QPushButton("Удалить", this);
    btnRefresh = new QPushButton("Обновить", this);
    
    buttonLayout->addWidget(btnAdd);
    buttonLayout->addWidget(btnEdit);
    buttonLayout->addWidget(btnDelete);
    buttonLayout->addWidget(btnRefresh);
    buttonLayout->addStretch();
    
    rightLayout->addLayout(buttonLayout);
    mainLayout->addLayout(rightLayout, 2);

    connect(btnAdd, &QPushButton::clicked, this, &OrdersWindow::onAddOrder);
    connect(btnEdit, &QPushButton::clicked, this, &OrdersWindow::onEditOrder);
    connect(btnDelete, &QPushButton::clicked, this, &OrdersWindow::onDeleteOrder);
    connect(btnRefresh, &QPushButton::clicked, this, &OrdersWindow::onRefresh);
}

void OrdersWindow::refreshOrderTable() {
    orderTable->setRowCount(0);
    
    QDate selectedDate = calendar->selectedDate();
    std::tm filterDate = {};
    filterDate.tm_year = selectedDate.year() - 1900;
    filterDate.tm_mon = selectedDate.month() - 1;
    filterDate.tm_mday = selectedDate.day();
    
    List<Order*> ordersForDate = orders->getOrdersByDate(filterDate);
    
    int row = 0;
    for (auto it = ordersForDate.begin(); it != ordersForDate.end(); ++it) {
        Order* order = *it;
        orderTable->insertRow(row);
        orderTable->setItem(row, 0, new QTableWidgetItem(QString::number(order->getId())));
        orderTable->setItem(row, 1, new QTableWidgetItem(QString::number(order->getVehicleId())));
        orderTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(order->getClientName())));
        orderTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(order->getClientPhone())));
        orderTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(order->getPickupAddress())));
        orderTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(order->getDestinationAddress())));
        
        std::tm orderTime = order->getOrderDateTime();
        QString dateTimeStr = QString("%1-%2-%3 %4:%5")
                             .arg(orderTime.tm_year + 1900, 4, 10, QChar('0'))
                             .arg(orderTime.tm_mon + 1, 2, 10, QChar('0'))
                             .arg(orderTime.tm_mday, 2, 10, QChar('0'))
                             .arg(orderTime.tm_hour, 2, 10, QChar('0'))
                             .arg(orderTime.tm_min, 2, 10, QChar('0'));
        orderTable->setItem(row, 6, new QTableWidgetItem(dateTimeStr));
        
        if (order->isCompleted()) {
            for (int col = 0; col < orderTable->columnCount(); ++col) {
                orderTable->item(row, col)->setBackground(Qt::lightGray);
            }
        }
        
        row++;
    }
}

void OrdersWindow::onAddOrder() {
    showAddOrderForm();
}

void OrdersWindow::onEditOrder() {
    Order* order = getSelectedOrder();
    if (order) {
        showOrderForm(order);
    } else {
        QMessageBox::warning(this, "Предупреждение", "Выберите заказ для редактирования");
    }
}

void OrdersWindow::onDeleteOrder() {
    Order* order = getSelectedOrder();
    if (!order) {
        QMessageBox::warning(this, "Предупреждение", "Выберите заказ для удаления");
        return;
    }
    
    int ret = QMessageBox::question(this, "Подтверждение", 
                                     "Вы уверены, что хотите удалить этот заказ?",
                                     QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        orders->removeOrder(order->getId());
        try {
            fileManager->saveOrders(*orders);
            refreshOrderTable();
            QMessageBox::information(this, "Успех", "Заказ удален");
        } catch (const TaxiParkException& e) {
            QMessageBox::critical(this, "Ошибка", 
                                 "Ошибка сохранения: " + QString::fromStdString(e.what()));
        }
    }
}

void OrdersWindow::onCalendarDateChanged() {
    refreshOrderTable();
}

void OrdersWindow::onRefresh() {
    refreshOrderTable();
}

void OrdersWindow::showAddOrderForm() {
    showOrderForm();
}

void OrdersWindow::showOrderForm(Order* order) {
    OrderForm form(order, vehicles, orders, this);
    if (form.exec() == QDialog::Accepted) {
        try {
            fileManager->saveOrders(*orders);
            refreshOrderTable();
        } catch (const TaxiParkException& e) {
            QMessageBox::critical(this, "Ошибка", 
                                 "Ошибка сохранения: " + QString::fromStdString(e.what()));
        }
    }
}

Order* OrdersWindow::getSelectedOrder() {
    int row = orderTable->currentRow();
    if (row < 0) {
        return nullptr;
    }
    
    QTableWidgetItem* idItem = orderTable->item(row, 0);
    if (!idItem) {
        return nullptr;
    }
    
    int id = idItem->text().toInt();
    return orders->findOrder(id);
}

bool OrdersWindow::isVehicleAvailable(int vehicleId, const std::tm& startTime, const std::tm& endTime, int excludeOrderId) {
    List<Order*> allOrders = orders->getOrdersByVehicle(vehicleId);
    
    for (auto it = allOrders.begin(); it != allOrders.end(); ++it) {
        Order* order = *it;
        if (order->getId() == excludeOrderId) {
            continue;
        }
        
        if (order->isCompleted()) {
            continue;
        }
        
        std::tm orderStart = order->getOrderDateTime();
        std::tm orderEnd = order->getReturnDateTime();
        
        // Проверить пересечение
        if (!(tmLess(endTime, orderStart) || tmGreater(startTime, orderEnd))) {
            return false;
        }
    }
    
    return true;
}

