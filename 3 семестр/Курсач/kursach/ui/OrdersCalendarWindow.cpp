#include "OrdersCalendarWindow.h"
#include "../core/Order.h"
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QMessageBox>
#include <QHeaderView>
#include <QTextCharFormat>
#include <QTextFormat>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QSet>
#include <ctime>

OrdersCalendarWindow::OrdersCalendarWindow(OrderList* orders, List<Vehicle*>* vehicles, QWidget* parent)
    : QDialog(parent), orders(orders), vehicles(vehicles) {
    setupUI();
    highlightDatesWithOrders();
    QDate currentDate = calendar->selectedDate();
    if (currentDate.isValid()) {
        onDateSelected(currentDate);
    }
}

void OrdersCalendarWindow::setupUI() {
    setWindowTitle("📅 Календарь заказов");
    setMinimumSize(900, 600);
    resize(1000, 700);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Заголовок с информацией о дате
    QHBoxLayout* headerLayout = new QHBoxLayout();
    dateLabel = new QLabel("Выберите дату", this);
    dateLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "    color: #2196F3;"
        "    padding: 10px;"
        "}"
    );
    ordersCountLabel = new QLabel("", this);
    ordersCountLabel->setStyleSheet(
        "QLabel {"
        "    font-size: 14px;"
        "    color: #666666;"
        "    padding: 10px;"
        "}"
    );
    headerLayout->addWidget(dateLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(ordersCountLabel);
    mainLayout->addLayout(headerLayout);

    // Основное содержимое: Календарь и список заказов
    QHBoxLayout* contentLayout = new QHBoxLayout();

    // Виджет календаря
    QGroupBox* calendarGroup = new QGroupBox("Календарь", this);
    QVBoxLayout* calendarLayout = new QVBoxLayout(calendarGroup);
    
    calendar = new QCalendarWidget(this);
    calendar->setGridVisible(true);
    calendar->setStyleSheet(
        "QCalendarWidget {"
        "    background-color: white;"
        "    border: 2px solid #e0e0e0;"
        "    border-radius: 8px;"
        "}"
        "QCalendarWidget QTableView {"
        "    selection-background-color: #E3F2FD;"
        "    selection-color: #1976D2;"
        "}"
        "QCalendarWidget QToolButton {"
        "    background-color: #2196F3;"
        "    color: white;"
        "    border-radius: 4px;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
        "QCalendarWidget QToolButton:hover {"
        "    background-color: #1976D2;"
        "}"
    );
    
    connect(calendar, &QCalendarWidget::selectionChanged, this, [this]() {
        onDateSelected(calendar->selectedDate());
    });
    calendarLayout->addWidget(calendar);
    contentLayout->addWidget(calendarGroup, 1);

    // Список заказов
    QGroupBox* ordersGroup = new QGroupBox("Заказы на выбранную дату", this);
    QVBoxLayout* ordersLayout = new QVBoxLayout(ordersGroup);
    
    ordersList = new QListWidget(this);
    ordersList->setStyleSheet(
        "QListWidget {"
        "    background-color: #f5f5f5;"
        "    border: 2px solid #e0e0e0;"
        "    border-radius: 8px;"
        "    font-size: 13px;"
        "    color: black;"
        "}"
        "QListWidget::item {"
        "    background-color: #E3F2FD;"
        "    border: 1px solid #BBDEFB;"
        "    border-radius: 8px;"
        "    padding: 12px;"
        "    margin: 5px;"
        "    color: black;"
        "    min-height: 120px;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #BBDEFB;"
        "    border: 2px solid #2196F3;"
        "    color: black;"
        "}"
        "QListWidget::item:hover {"
        "    background-color: #BBDEFB;"
        "    border: 2px solid #64B5F6;"
        "    color: black;"
        "}"
    );
    ordersList->setAlternatingRowColors(false);
    connect(ordersList, &QListWidget::itemDoubleClicked, this, &OrdersCalendarWindow::onOrderDoubleClicked);
    ordersLayout->addWidget(ordersList);
    
    contentLayout->addWidget(ordersGroup, 1);
    mainLayout->addLayout(contentLayout);

    // Кнопки
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    refreshButton = new QPushButton("🔄 Обновить", this);
    closeButton = new QPushButton("✖️ Закрыть", this);
    closeButton->setProperty("class", "btnDelete");
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);

    connect(refreshButton, &QPushButton::clicked, this, &OrdersCalendarWindow::onRefresh);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
}

void OrdersCalendarWindow::onDateSelected(const QDate& date) {
    if (date.isValid()) {
        dateLabel->setText("📅 " + date.toString("dd.MM.yyyy (dddd)"));
        updateOrdersList(date);
    }
}

void OrdersCalendarWindow::updateOrdersList(const QDate& date) {
    ordersList->clear();
    
    // Преобразовать QDate в std::tm
    std::tm dateTm = {};
    dateTm.tm_year = date.year() - 1900;
    dateTm.tm_mon = date.month() - 1;
    dateTm.tm_mday = date.day();
    
    List<Order*> ordersOnDate = orders->getOrdersByDate(dateTm);
    
    int count = 0;
    for (auto it = ordersOnDate.begin(); it != ordersOnDate.end(); ++it) {
        Order* order = *it;
        if (order) {
            QString orderText = formatOrderInfo(*order);
            QListWidgetItem* item = new QListWidgetItem(orderText, ordersList);
            item->setData(Qt::UserRole, order->getId());
            item->setForeground(QBrush(QColor(Qt::black)));
            item->setFont(QFont("Segoe UI", 11));
            ordersList->addItem(item);
            count++;
        }
    }
    
    if (count == 0) {
        QListWidgetItem* item = new QListWidgetItem("На эту дату заказов нет", ordersList);
        item->setFlags(Qt::NoItemFlags);
        item->setForeground(QBrush(QColor(Qt::black)));
        ordersList->addItem(item);
    }
    
    ordersCountLabel->setText(QString("Всего заказов: %1").arg(count));
}

void OrdersCalendarWindow::highlightDatesWithOrders() {
    // Получить все уникальные даты с заказами
    QSet<QDate> datesWithOrders;
    
    for (int i = 0; i < static_cast<int>(orders->size()); ++i) {
        Order* order = orders->getOrder(i);
        if (order) {
            std::tm orderTm = order->getOrderDateTime();
            QDate orderDate(orderTm.tm_year + 1900, orderTm.tm_mon + 1, orderTm.tm_mday);
            datesWithOrders.insert(orderDate);
        }
    }
    
    // Применить форматирование к датам с заказами
    QTextCharFormat format;
    format.setBackground(QBrush(QColor("#E3F2FD")));
    format.setForeground(QBrush(QColor("#1976D2")));
    format.setFontWeight(QFont::Bold);
    
    for (const QDate& date : datesWithOrders) {
        calendar->setDateTextFormat(date, format);
    }
}

QString OrdersCalendarWindow::formatOrderInfo(const Order& order) {
    QString info;
    
    // Найти транспортное средство
    QString vehicleInfo = "Неизвестный автомобиль";
    for (auto it = vehicles->begin(); it != vehicles->end(); ++it) {
        if ((*it)->getId() == order.getVehicleId()) {
            vehicleInfo = QString::fromStdString((*it)->getBrand() + " " + (*it)->getModel());
            break;
        }
    }
    
    // Преобразовать std::tm в QDateTime
    std::tm orderTm = order.getOrderDateTime();
    std::tm returnTm = order.getReturnDateTime();
    
    QDateTime orderDateTime(
        QDate(orderTm.tm_year + 1900, orderTm.tm_mon + 1, orderTm.tm_mday),
        QTime(orderTm.tm_hour, orderTm.tm_min, orderTm.tm_sec)
    );
    QDateTime returnDateTime(
        QDate(returnTm.tm_year + 1900, returnTm.tm_mon + 1, returnTm.tm_mday),
        QTime(returnTm.tm_hour, returnTm.tm_min, returnTm.tm_sec)
    );
    
    // Форматирование с иконками, как на изображении
    info = QString("🚗 %1\n")
           .arg(vehicleInfo);
    info += QString("👤 Клиент: %1\n")
           .arg(QString::fromStdString(order.getClientName()));
    info += QString("📞 Телефон: %1\n")
           .arg(QString::fromStdString(order.getClientPhone()));
    info += QString("📍 Откуда: %1\n")
           .arg(QString::fromStdString(order.getPickupAddress()));
    info += QString("📍 Куда: %1\n")
           .arg(QString::fromStdString(order.getDestinationAddress()));
    info += QString("⏰ Время: %1 - %2\n")
           .arg(orderDateTime.toString("hh:mm"))
           .arg(returnDateTime.toString("hh:mm"));
    info += QString("✅ Статус: %1")
           .arg(order.isCompleted() ? "Завершен" : "Активен");
    
    return info;
}

void OrdersCalendarWindow::onOrderDoubleClicked(QListWidgetItem* item) {
    if (!item || item->flags() == Qt::NoItemFlags) {
        return;
    }
    
    int orderId = item->data(Qt::UserRole).toInt();
    Order* order = orders->findOrder(orderId);
    
    if (order) {
        QString details = "Детали заказа #" + QString::number(orderId) + "\n\n";
        details += formatOrderInfo(*order);
        
        QMessageBox::information(this, "Детали заказа", details);
    }
}

void OrdersCalendarWindow::onRefresh() {
    highlightDatesWithOrders();
    onDateSelected(calendar->selectedDate());
}

