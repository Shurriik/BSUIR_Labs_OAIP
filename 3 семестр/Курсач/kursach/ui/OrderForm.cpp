#include "OrderForm.h"
#include <QMessageBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
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

OrderForm::OrderForm(Order* order, List<Vehicle*>* vehicles, OrderList* orders, QWidget* parent)
    : QDialog(parent), editingOrder(order), vehicles(vehicles), orders(orders) {
    setupUI();
    if (order) {
        loadOrderData();
    }
}

OrderForm::~OrderForm() {
}

void OrderForm::setupUI() {
    setWindowTitle(editingOrder ? "Редактирование заказа" : "Новый заказ");
    setMinimumWidth(500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();

    vehicleCombo = new QComboBox(this);
    for (auto it = vehicles->begin(); it != vehicles->end(); ++it) {
        Vehicle* v = *it;
        QString text = QString("%1 - %2 %3 (ID: %4)")
                      .arg(v->getId())
                      .arg(QString::fromStdString(v->getBrand()))
                      .arg(QString::fromStdString(v->getModel()))
                      .arg(v->getId());
        vehicleCombo->addItem(text, v->getId());
    }
    connect(vehicleCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &OrderForm::onVehicleChanged);
    formLayout->addRow("Автомобиль:", vehicleCombo);

    clientNameEdit = new QLineEdit(this);
    formLayout->addRow("Имя клиента:", clientNameEdit);

    clientPhoneEdit = new QLineEdit(this);
    formLayout->addRow("Телефон:", clientPhoneEdit);

    pickupAddressEdit = new QLineEdit(this);
    formLayout->addRow("Адрес отправления:", pickupAddressEdit);

    destinationAddressEdit = new QLineEdit(this);
    formLayout->addRow("Адрес назначения:", destinationAddressEdit);

    orderDateTimeEdit = new QDateTimeEdit(this);
    orderDateTimeEdit->setCalendarPopup(true);
    orderDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    formLayout->addRow("Дата/время заказа:", orderDateTimeEdit);

    returnDateTimeEdit = new QDateTimeEdit(this);
    returnDateTimeEdit->setCalendarPopup(true);
    returnDateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));
    formLayout->addRow("Дата/время возврата:", returnDateTimeEdit);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("Сохранить", this);
    cancelButton = new QPushButton("Отмена", this);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &OrderForm::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &OrderForm::onCancel);
}

void OrderForm::loadOrderData() {
    if (!editingOrder) return;

    // Найти транспортное средство в комбобоксе
    int vehicleId = editingOrder->getVehicleId();
    for (int i = 0; i < vehicleCombo->count(); ++i) {
        if (vehicleCombo->itemData(i).toInt() == vehicleId) {
            vehicleCombo->setCurrentIndex(i);
            break;
        }
    }

    clientNameEdit->setText(QString::fromStdString(editingOrder->getClientName()));
    clientPhoneEdit->setText(QString::fromStdString(editingOrder->getClientPhone()));
    pickupAddressEdit->setText(QString::fromStdString(editingOrder->getPickupAddress()));
    destinationAddressEdit->setText(QString::fromStdString(editingOrder->getDestinationAddress()));

    std::tm orderTime = editingOrder->getOrderDateTime();
    QDateTime orderDateTime(QDate(orderTime.tm_year + 1900, orderTime.tm_mon + 1, orderTime.tm_mday),
                           QTime(orderTime.tm_hour, orderTime.tm_min, orderTime.tm_sec));
    orderDateTimeEdit->setDateTime(orderDateTime);

    std::tm returnTime = editingOrder->getReturnDateTime();
    QDateTime returnDateTime(QDate(returnTime.tm_year + 1900, returnTime.tm_mon + 1, returnTime.tm_mday),
                            QTime(returnTime.tm_hour, returnTime.tm_min, returnTime.tm_sec));
    returnDateTimeEdit->setDateTime(returnDateTime);
}

void OrderForm::onVehicleChanged(int index) {
    // Можно добавить валидацию здесь
}

void OrderForm::onSave() {
    if (!validateInput()) {
        return;
    }

    if (!checkVehicleAvailability()) {
        QMessageBox::warning(this, "Предупреждение", 
                            "Выбранный автомобиль недоступен в указанное время");
        return;
    }

    try {
        int vehicleId = vehicleCombo->currentData().toInt();
        std::string clientName = clientNameEdit->text().toStdString();
        std::string clientPhone = clientPhoneEdit->text().toStdString();
        std::string pickupAddress = pickupAddressEdit->text().toStdString();
        std::string destinationAddress = destinationAddressEdit->text().toStdString();

        QDateTime orderQt = orderDateTimeEdit->dateTime();
        QDateTime returnQt = returnDateTimeEdit->dateTime();

        std::tm orderTime = {};
        orderTime.tm_year = orderQt.date().year() - 1900;
        orderTime.tm_mon = orderQt.date().month() - 1;
        orderTime.tm_mday = orderQt.date().day();
        orderTime.tm_hour = orderQt.time().hour();
        orderTime.tm_min = orderQt.time().minute();
        orderTime.tm_sec = orderQt.time().second();

        std::tm returnTime = {};
        returnTime.tm_year = returnQt.date().year() - 1900;
        returnTime.tm_mon = returnQt.date().month() - 1;
        returnTime.tm_mday = returnQt.date().day();
        returnTime.tm_hour = returnQt.time().hour();
        returnTime.tm_min = returnQt.time().minute();
        returnTime.tm_sec = returnQt.time().second();

        if (editingOrder) {
            editingOrder->setVehicleId(vehicleId);
            editingOrder->setClientName(clientName);
            editingOrder->setClientPhone(clientPhone);
            editingOrder->setPickupAddress(pickupAddress);
            editingOrder->setDestinationAddress(destinationAddress);
            editingOrder->setOrderDateTime(orderTime);
            editingOrder->setReturnDateTime(returnTime);
        } else {
            Order newOrder(vehicleId, clientName, clientPhone, pickupAddress, 
                          destinationAddress, orderTime, returnTime);
            orders->addOrder(newOrder);
        }

        accept();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", 
                             "Ошибка сохранения: " + QString::fromStdString(e.what()));
    }
}

void OrderForm::onCancel() {
    reject();
}

bool OrderForm::validateInput() {
    if (vehicleCombo->currentIndex() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите автомобиль");
        return false;
    }
    if (clientNameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя клиента");
        return false;
    }
    if (clientPhoneEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите телефон");
        return false;
    }
    if (pickupAddressEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите адрес отправления");
        return false;
    }
    if (destinationAddressEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите адрес назначения");
        return false;
    }
    if (returnDateTimeEdit->dateTime() <= orderDateTimeEdit->dateTime()) {
        QMessageBox::warning(this, "Ошибка", "Время возврата должно быть позже времени заказа");
        return false;
    }
    return true;
}

bool OrderForm::checkVehicleAvailability() {
    int vehicleId = vehicleCombo->currentData().toInt();
    
    QDateTime orderQt = orderDateTimeEdit->dateTime();
    QDateTime returnQt = returnDateTimeEdit->dateTime();

    std::tm orderTime = {};
    orderTime.tm_year = orderQt.date().year() - 1900;
    orderTime.tm_mon = orderQt.date().month() - 1;
    orderTime.tm_mday = orderQt.date().day();
    orderTime.tm_hour = orderQt.time().hour();
    orderTime.tm_min = orderQt.time().minute();

    std::tm returnTime = {};
    returnTime.tm_year = returnQt.date().year() - 1900;
    returnTime.tm_mon = returnQt.date().month() - 1;
    returnTime.tm_mday = returnQt.date().day();
    returnTime.tm_hour = returnQt.time().hour();
    returnTime.tm_min = returnQt.time().minute();

    int excludeOrderId = editingOrder ? editingOrder->getId() : -1;
    
    List<Order*> allOrders = orders->getOrdersByVehicle(vehicleId);
    for (auto it = allOrders.begin(); it != allOrders.end(); ++it) {
        Order* order = *it;
        if (order->getId() == excludeOrderId || order->isCompleted()) {
            continue;
        }
        
        std::tm orderStart = order->getOrderDateTime();
        std::tm orderEnd = order->getReturnDateTime();
        
        // Простая проверка пересечения
        if (!(tmLess(returnTime, orderStart) || tmGreater(orderTime, orderEnd))) {
            return false;
        }
    }
    
    return true;
}

