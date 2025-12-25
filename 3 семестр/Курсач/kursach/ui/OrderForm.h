#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QFormLayout>
#include "../core/Order.h"
#include "../core/OrderList.h"
#include "../core/Vehicle.h"
#include "../core/List.h"

class OrderForm : public QDialog {
    Q_OBJECT

public:
    OrderForm(Order* order, List<Vehicle*>* vehicles, OrderList* orders, QWidget* parent = nullptr);
    ~OrderForm();

private slots:
    void onSave();
    void onCancel();
    void onVehicleChanged(int index);

private:
    void setupUI();
    void loadOrderData();
    bool validateInput();
    bool checkVehicleAvailability();

    Order* editingOrder;
    List<Vehicle*>* vehicles;
    OrderList* orders;

    QComboBox* vehicleCombo;
    QLineEdit* clientNameEdit;
    QLineEdit* clientPhoneEdit;
    QLineEdit* pickupAddressEdit;
    QLineEdit* destinationAddressEdit;
    QDateTimeEdit* orderDateTimeEdit;
    QDateTimeEdit* returnDateTimeEdit;
    QPushButton* saveButton;
    QPushButton* cancelButton;
};

#endif // ORDERFORM_H

