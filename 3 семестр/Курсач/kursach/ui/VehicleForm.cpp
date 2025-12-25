#include "VehicleForm.h"
#include "../vehicles/EconomyCar.h"
#include "../vehicles/ComfortCar.h"
#include "../vehicles/BusinessCar.h"
#include "../vehicles/Minivan.h"
#include "../exceptions/TaxiParkException.h"
#include <QMessageBox>

VehicleForm::VehicleForm(Vehicle* vehicle, List<Vehicle*>* vehicles, FileManager* fileManager, QWidget* parent)
    : QDialog(parent), editingVehicle(vehicle), vehicles(vehicles), fileManager(fileManager) {
    setupUI();
    if (vehicle) {
        loadVehicleData();
    }
}

VehicleForm::~VehicleForm() {
}

void VehicleForm::setupUI() {
    setWindowTitle(editingVehicle ? "Редактирование автомобиля" : "Добавление автомобиля");
    setMinimumWidth(500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QFormLayout* formLayout = new QFormLayout();

    // Общие поля
    brandEdit = new QLineEdit(this);
    formLayout->addRow("Марка:", brandEdit);

    modelEdit = new QLineEdit(this);
    formLayout->addRow("Модель:", modelEdit);

    yearSpin = new QSpinBox(this);
    yearSpin->setRange(1900, 2100);
    yearSpin->setValue(2020);
    formLayout->addRow("Год выпуска:", yearSpin);

    licensePlateEdit = new QLineEdit(this);
    formLayout->addRow("Госномер:", licensePlateEdit);

    mileageSpin = new QSpinBox(this);
    mileageSpin->setRange(0, 1000000);
    mileageSpin->setValue(0);
    formLayout->addRow("Пробег (км):", mileageSpin);

    statusCombo = new QComboBox(this);
    statusCombo->addItem("На линии", 0);
    statusCombo->addItem("В парке", 1);
    statusCombo->addItem("В ремонте", 2);
    formLayout->addRow("Статус:", statusCombo);

    vehicleTypeCombo = new QComboBox(this);
    vehicleTypeCombo->addItem("Эконом", 0);
    vehicleTypeCombo->addItem("Комфорт", 1);
    vehicleTypeCombo->addItem("Бизнес", 2);
    vehicleTypeCombo->addItem("Минивэн", 3);
    connect(vehicleTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VehicleForm::onVehicleTypeChanged);
    formLayout->addRow("Тип ТС:", vehicleTypeCombo);

    seatsSpin = new QSpinBox(this);
    seatsSpin->setRange(1, 20);
    seatsSpin->setValue(4);
    formLayout->addRow("Количество мест:", seatsSpin);

    categoryEdit = new QLineEdit(this);
    categoryEdit->setText("Standard");
    formLayout->addRow("Категория:", categoryEdit);

    mainLayout->addLayout(formLayout);

    // Группа специфических полей
    QGroupBox* specificGroup = new QGroupBox("Дополнительные параметры", this);
    QFormLayout* specificLayout = new QFormLayout(specificGroup);

    basePriceSpin = new QDoubleSpinBox(this);
    basePriceSpin->setRange(0, 10000);
    basePriceSpin->setValue(100);
    basePriceSpin->setDecimals(2);
    specificLayout->addRow("Цена за час (руб/час):", basePriceSpin);
    
    luggageCapacitySpin = new QSpinBox(this);
    luggageCapacitySpin->setRange(0, 2000);
    luggageCapacitySpin->setValue(300);
    specificLayout->addRow("Объем багажника (л):", luggageCapacitySpin);

    climateControlCheck = new QCheckBox(this);
    climateControlCheck->setChecked(true);
    specificLayout->addRow("Климат-контроль:", climateControlCheck);

    seatHeatingCheck = new QCheckBox(this);
    seatHeatingCheck->setChecked(false);
    specificLayout->addRow("Подогрев сидений:", seatHeatingCheck);

    seatMassageCheck = new QCheckBox(this);
    seatMassageCheck->setChecked(false);
    specificLayout->addRow("Массаж сидений:", seatMassageCheck);

    navigationCheck = new QCheckBox(this);
    navigationCheck->setChecked(false);
    specificLayout->addRow("Навигация:", navigationCheck);

    cruiseControlCheck = new QCheckBox(this);
    cruiseControlCheck->setChecked(false);
    specificLayout->addRow("Круиз-контроль:", cruiseControlCheck);

    steeringWheelHeatingCheck = new QCheckBox(this);
    steeringWheelHeatingCheck->setChecked(false);
    specificLayout->addRow("Подогрев руля:", steeringWheelHeatingCheck);

    leatherSeatsCheck = new QCheckBox(this);
    leatherSeatsCheck->setChecked(true);
    specificLayout->addRow("Кожаные сиденья:", leatherSeatsCheck);

    premiumAudioCheck = new QCheckBox(this);
    premiumAudioCheck->setChecked(true);
    specificLayout->addRow("Премиум аудио:", premiumAudioCheck);

    childSeatsCheck = new QCheckBox(this);
    childSeatsCheck->setChecked(true);
    specificLayout->addRow("Детские кресла:", childSeatsCheck);

    mainLayout->addWidget(specificGroup);

    // Кнопки
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("Сохранить", this);
    cancelButton = new QPushButton("Отмена", this);
    buttonLayout->addStretch();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &VehicleForm::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &VehicleForm::onCancel);

    onVehicleTypeChanged(0);
}

void VehicleForm::loadVehicleData() {
    if (!editingVehicle) return;

    brandEdit->setText(QString::fromStdString(editingVehicle->getBrand()));
    modelEdit->setText(QString::fromStdString(editingVehicle->getModel()));
    yearSpin->setValue(editingVehicle->getYear());
    licensePlateEdit->setText(QString::fromStdString(editingVehicle->getLicensePlate()));
    mileageSpin->setValue(editingVehicle->getMileage());
    statusCombo->setCurrentIndex(static_cast<int>(editingVehicle->getStatus()));

    TaxiVehicle* taxiVehicle = dynamic_cast<TaxiVehicle*>(editingVehicle);
    if (taxiVehicle) {
        vehicleTypeCombo->setCurrentIndex(static_cast<int>(taxiVehicle->getVehicleType()));
        seatsSpin->setValue(taxiVehicle->getSeats());
        categoryEdit->setText(QString::fromStdString(taxiVehicle->getCategory()));

        basePriceSpin->setValue(0);
        luggageCapacitySpin->setValue(taxiVehicle->getLuggageCapacity());
        
        // Загрузить все опции для всех типов транспортных средств
        if (EconomyCar* ec = dynamic_cast<EconomyCar*>(editingVehicle)) {
            basePriceSpin->setValue(ec->getHourlyPrice());
            climateControlCheck->setChecked(ec->getHasClimateControl());
            seatHeatingCheck->setChecked(ec->getHasSeatHeating());
            seatMassageCheck->setChecked(ec->getHasSeatMassage());
            navigationCheck->setChecked(ec->getHasNavigation());
            cruiseControlCheck->setChecked(ec->getHasCruiseControl());
            steeringWheelHeatingCheck->setChecked(ec->getHasSteeringWheelHeating());
            leatherSeatsCheck->setChecked(ec->getHasLeatherSeats());
            premiumAudioCheck->setChecked(ec->getHasPremiumAudio());
            childSeatsCheck->setChecked(ec->getHasChildSeats());
        } else if (ComfortCar* cc = dynamic_cast<ComfortCar*>(editingVehicle)) {
            basePriceSpin->setValue(cc->getHourlyPrice());
            climateControlCheck->setChecked(cc->getHasClimateControl());
            seatHeatingCheck->setChecked(cc->getHasSeatHeating());
            seatMassageCheck->setChecked(cc->getHasSeatMassage());
            navigationCheck->setChecked(cc->getHasNavigation());
            cruiseControlCheck->setChecked(cc->getHasCruiseControl());
            steeringWheelHeatingCheck->setChecked(cc->getHasSteeringWheelHeating());
            leatherSeatsCheck->setChecked(cc->getHasLeatherSeats());
            premiumAudioCheck->setChecked(cc->getHasPremiumAudio());
            childSeatsCheck->setChecked(cc->getHasChildSeats());
        } else if (BusinessCar* bc = dynamic_cast<BusinessCar*>(editingVehicle)) {
            basePriceSpin->setValue(bc->getHourlyPrice());
            climateControlCheck->setChecked(bc->getHasClimateControl());
            seatHeatingCheck->setChecked(bc->getHasSeatHeating());
            seatMassageCheck->setChecked(bc->getHasSeatMassage());
            navigationCheck->setChecked(bc->getHasNavigation());
            cruiseControlCheck->setChecked(bc->getHasCruiseControl());
            steeringWheelHeatingCheck->setChecked(bc->getHasSteeringWheelHeating());
            leatherSeatsCheck->setChecked(bc->getHasLeatherSeats());
            premiumAudioCheck->setChecked(bc->getHasPremiumAudio());
            childSeatsCheck->setChecked(bc->getHasChildSeats());
        } else if (Minivan* mv = dynamic_cast<Minivan*>(editingVehicle)) {
            basePriceSpin->setValue(mv->getHourlyPrice());
            climateControlCheck->setChecked(mv->getHasClimateControl());
            seatHeatingCheck->setChecked(mv->getHasSeatHeating());
            seatMassageCheck->setChecked(mv->getHasSeatMassage());
            navigationCheck->setChecked(mv->getHasNavigation());
            cruiseControlCheck->setChecked(mv->getHasCruiseControl());
            steeringWheelHeatingCheck->setChecked(mv->getHasSteeringWheelHeating());
            leatherSeatsCheck->setChecked(mv->getHasLeatherSeats());
            premiumAudioCheck->setChecked(mv->getHasPremiumAudio());
            childSeatsCheck->setChecked(mv->getHasChildSeats());
        }
    }

    onVehicleTypeChanged(vehicleTypeCombo->currentIndex());
}

void VehicleForm::onVehicleTypeChanged(int index) {
    // Все опции теперь видны для всех типов транспортных средств
    climateControlCheck->setVisible(true);
    seatHeatingCheck->setVisible(true);
    seatMassageCheck->setVisible(true);
    navigationCheck->setVisible(true);
    cruiseControlCheck->setVisible(true);
    steeringWheelHeatingCheck->setVisible(true);
    leatherSeatsCheck->setVisible(true);
    premiumAudioCheck->setVisible(true);
    childSeatsCheck->setVisible(true);
    luggageCapacitySpin->setVisible(true);
}

void VehicleForm::onSave() {
    if (!validateInput()) {
        return;
    }

    try {
        if (editingVehicle) {
            // Обновить существующее транспортное средство - создать новое и заменить
            Vehicle* newVehicle = createVehicleFromForm();
            int id = editingVehicle->getId();
            
            // Найти и заменить в списке
            for (auto it = vehicles->begin(); it != vehicles->end(); ++it) {
                if (*it == editingVehicle) {
                    delete editingVehicle;
                    *it = newVehicle;
                    newVehicle->setId(id);
                    break;
                }
            }
            
            fileManager->saveVehicle(newVehicle);
        } else {
            // Добавить новое транспортное средство
            Vehicle* vehicle = createVehicleFromForm();
            vehicles->push_back(vehicle);
            fileManager->saveVehicle(vehicle);
        }
        
        accept();
    } catch (const TaxiParkException& e) {
        QMessageBox::critical(this, "Ошибка", 
                             "Ошибка сохранения: " + QString::fromStdString(e.what()));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", 
                             "Ошибка: " + QString::fromStdString(e.what()));
    }
}

void VehicleForm::onCancel() {
    reject();
}

bool VehicleForm::validateInput() {
    if (brandEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите марку автомобиля");
        return false;
    }
    if (modelEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите модель автомобиля");
        return false;
    }
    if (licensePlateEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите госномер");
        return false;
    }
    return true;
}

Vehicle* VehicleForm::createVehicleFromForm() {
    std::string brand = brandEdit->text().toStdString();
    std::string model = modelEdit->text().toStdString();
    int year = yearSpin->value();
    std::string licensePlate = licensePlateEdit->text().toStdString();
    int mileage = mileageSpin->value();
    VehicleStatus status = static_cast<VehicleStatus>(statusCombo->currentIndex());
    int seats = seatsSpin->value();
    std::string category = categoryEdit->text().toStdString();
    double basePrice = basePriceSpin->value();

    Vehicle* vehicle = nullptr;
    int typeIndex = vehicleTypeCombo->currentIndex();

    int luggageCapacity = luggageCapacitySpin->value();
    
    switch (typeIndex) {
        case 0: // Эконом
            vehicle = new EconomyCar(brand, model, year, licensePlate, mileage, status,
                                     seats, category, luggageCapacity, basePrice,
                                     climateControlCheck->isChecked(),
                                     seatHeatingCheck->isChecked(), seatMassageCheck->isChecked(),
                                     navigationCheck->isChecked(), cruiseControlCheck->isChecked(),
                                     steeringWheelHeatingCheck->isChecked(),
                                     leatherSeatsCheck->isChecked(), premiumAudioCheck->isChecked(),
                                     childSeatsCheck->isChecked());
            break;
        case 1: // Комфорт
            vehicle = new ComfortCar(brand, model, year, licensePlate, mileage, status,
                                    seats, category, luggageCapacity, basePrice, 
                                    climateControlCheck->isChecked(),
                                    seatHeatingCheck->isChecked(), seatMassageCheck->isChecked(),
                                    navigationCheck->isChecked(), cruiseControlCheck->isChecked(),
                                    steeringWheelHeatingCheck->isChecked(),
                                    leatherSeatsCheck->isChecked(), premiumAudioCheck->isChecked(),
                                    childSeatsCheck->isChecked());
            break;
        case 2: // Бизнес
            vehicle = new BusinessCar(brand, model, year, licensePlate, mileage, status,
                                     seats, category, luggageCapacity, basePrice,
                                     climateControlCheck->isChecked(),
                                     seatHeatingCheck->isChecked(), seatMassageCheck->isChecked(),
                                     navigationCheck->isChecked(), cruiseControlCheck->isChecked(),
                                     steeringWheelHeatingCheck->isChecked(),
                                     leatherSeatsCheck->isChecked(), premiumAudioCheck->isChecked(),
                                     childSeatsCheck->isChecked());
            break;
        case 3: // Минивэн
            vehicle = new Minivan(brand, model, year, licensePlate, mileage, status,
                                 seats, category, luggageCapacity, basePrice,
                                 climateControlCheck->isChecked(),
                                 seatHeatingCheck->isChecked(), seatMassageCheck->isChecked(),
                                 navigationCheck->isChecked(), cruiseControlCheck->isChecked(),
                                 steeringWheelHeatingCheck->isChecked(),
                                 leatherSeatsCheck->isChecked(), premiumAudioCheck->isChecked(),
                                 childSeatsCheck->isChecked());
            break;
    }

    return vehicle;
}

