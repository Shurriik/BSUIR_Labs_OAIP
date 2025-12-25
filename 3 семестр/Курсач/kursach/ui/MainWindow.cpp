#include "MainWindow.h"
#include "VehicleForm.h"
#include "OrdersWindow.h"
#include "OrdersCalendarWindow.h"
#include "StatisticsWindow.h"
#include "../vehicles/EconomyCar.h"
#include "../vehicles/ComfortCar.h"
#include "../vehicles/BusinessCar.h"
#include "../vehicles/Minivan.h"
#include "../vehicles/TaxiVehicle.h"
#include "../exceptions/TaxiParkException.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QApplication>
#include <QDateTime>
#include <QAbstractItemView>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Загрузка стилей
    QFile styleFile("ui/styles.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&styleFile);
        QString style = stream.readAll();
        this->setStyleSheet(style);
        styleFile.close();
    }
    
    setupUI();
    try {
        loadVehicles();
        refreshVehicleTable();
        logOperation("Приложение запущено");
    } catch (...) {
        // Игнорируем ошибки при загрузке, чтобы приложение могло запуститься
        logOperation("Ошибка при загрузке данных");
    }
}

MainWindow::~MainWindow() {
    // Очистить транспортные средства
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        delete *it;
    }
}

void MainWindow::setupUI() {
    setWindowTitle("🚕 Управление таксопарком");
    setMinimumSize(1000, 600);
    resize(1200, 700);

    // Центральный виджет
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Группа фильтров
    QGroupBox* filterGroup = new QGroupBox("🔍 Фильтры", this);
    filterGroup->setStyleSheet(
        "QGroupBox {"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    color: #2196F3;"
        "}"
    );
    QHBoxLayout* filterLayout = new QHBoxLayout(filterGroup);
    
    filterLayout->addWidget(new QLabel("Марка:", this));
    filterBrand = new QLineEdit(this);
    filterBrand->setPlaceholderText("Введите марку");
    filterLayout->addWidget(filterBrand);
    
    filterLayout->addWidget(new QLabel("Модель:", this));
    filterModel = new QLineEdit(this);
    filterModel->setPlaceholderText("Введите модель");
    filterLayout->addWidget(filterModel);
    
    filterLayout->addWidget(new QLabel("Статус:", this));
    filterStatus = new QComboBox(this);
    filterStatus->addItem("Все", -1);
    filterStatus->addItem("На линии", 0);
    filterStatus->addItem("В парке", 1);
    filterStatus->addItem("В ремонте", 2);
    filterLayout->addWidget(filterStatus);
    
    filterLayout->addWidget(new QLabel("Тип:", this));
    filterType = new QComboBox(this);
    filterType->addItem("Все", -1);
    filterType->addItem("Эконом", 0);
    filterType->addItem("Комфорт", 1);
    filterType->addItem("Бизнес", 2);
    filterType->addItem("Минивэн", 3);
    filterLayout->addWidget(filterType);
    
    connect(filterBrand, &QLineEdit::textChanged, this, &MainWindow::onFilterChanged);
    connect(filterModel, &QLineEdit::textChanged, this, &MainWindow::onFilterChanged);
    connect(filterStatus, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFilterChanged);
    connect(filterType, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFilterChanged);
    
    mainLayout->addWidget(filterGroup);

    // Таблица транспортных средств
    vehicleTable = new QTableWidget(this);
    vehicleTable->setColumnCount(9);
    vehicleTable->setHorizontalHeaderLabels(QStringList() 
        << "ID" << "Марка" << "Модель" << "Год" << "Госномер" 
        << "Пробег" << "Статус" << "Тип" << "Мест");
    vehicleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    vehicleTable->setSelectionMode(QAbstractItemView::SingleSelection);
    vehicleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vehicleTable->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(vehicleTable);

    // Кнопки
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    
    btnAddVehicle = new QPushButton("➕ Добавить авто", this);
    btnEditVehicle = new QPushButton("✏️ Редактировать", this);
    btnDeleteVehicle = new QPushButton("🗑️ Удалить", this);
    btnRefresh = new QPushButton("🔄 Обновить", this);
    btnViewOrders = new QPushButton("📋 Заказы", this);
    btnAddOrder = new QPushButton("➕ Новый заказ", this);
    btnStatistics = new QPushButton("📊 Статистика", this);
    QPushButton* btnOrdersCalendar = new QPushButton("📅 Календарь заказов", this);
    btnSave = new QPushButton("💾 Сохранить", this);
    btnLoad = new QPushButton("📂 Загрузить", this);
    btnUndo = new QPushButton("↶ Отменить", this);
    btnRedo = new QPushButton("↷ Повторить", this);
    btnUndo->setEnabled(false);
    btnRedo->setEnabled(false);
    
    // Установка классов для стилизации
    btnAddVehicle->setProperty("class", "btnAdd");
    btnAddOrder->setProperty("class", "btnAdd");
    btnEditVehicle->setProperty("class", "btnEdit");
    btnDeleteVehicle->setProperty("class", "btnDelete");
    btnUndo->setProperty("class", "btnUndo");
    btnRedo->setProperty("class", "btnRedo");
    btnSave->setProperty("class", "btnSave");
    btnLoad->setProperty("class", "btnLoad");
    
    buttonLayout->addWidget(btnAddVehicle);
    buttonLayout->addWidget(btnEditVehicle);
    buttonLayout->addWidget(btnDeleteVehicle);
    buttonLayout->addWidget(btnRefresh);
    buttonLayout->addWidget(btnViewOrders);
    buttonLayout->addWidget(btnAddOrder);
    buttonLayout->addWidget(btnOrdersCalendar);
    buttonLayout->addWidget(btnStatistics);
    buttonLayout->addWidget(btnLoad);
    buttonLayout->addWidget(btnSave);
    buttonLayout->addWidget(btnUndo);
    buttonLayout->addWidget(btnRedo);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);

    // Подключить сигналы
    connect(btnAddVehicle, &QPushButton::clicked, this, &MainWindow::onAddVehicle);
    connect(btnEditVehicle, &QPushButton::clicked, this, &MainWindow::onEditVehicle);
    connect(btnDeleteVehicle, &QPushButton::clicked, this, &MainWindow::onDeleteVehicle);
    connect(btnRefresh, &QPushButton::clicked, this, &MainWindow::onRefreshVehicles);
    connect(btnViewOrders, &QPushButton::clicked, this, &MainWindow::onViewOrders);
    connect(btnAddOrder, &QPushButton::clicked, this, &MainWindow::onAddOrder);
    connect(btnOrdersCalendar, &QPushButton::clicked, this, &MainWindow::onViewOrdersCalendar);
    connect(btnStatistics, &QPushButton::clicked, this, &MainWindow::onViewStatistics);
    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::onLoadData);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::onSaveData);
    connect(btnUndo, &QPushButton::clicked, this, &MainWindow::onUndo);
    connect(btnRedo, &QPushButton::clicked, this, &MainWindow::onRedo);

    // Строка состояния
    statusLabel = new QLabel("✅ Готово", this);
    statusLabel->setStyleSheet(
        "QLabel {"
        "    padding: 5px;"
        "    color: #4CAF50;"
        "    font-weight: bold;"
        "}"
    );
    QMainWindow::statusBar()->addWidget(statusLabel);
}

void MainWindow::loadVehicles() {
    try {
        List<Vehicle*> loadedVehicles = fileManager.loadAllVehicles();
        for (auto it = loadedVehicles.begin(); it != loadedVehicles.end(); ++it) {
            vehicles.push_back(*it);
        }
        orders = fileManager.loadOrders();
        historyManager.clear();
        updateUndoRedoButtons();
        logOperation(QString("Данные загружены: автомобилей %1, заказов %2")
                    .arg(vehicles.size())
                    .arg(orders.size()));
    } catch (const TaxiParkException& e) {
        showError("Ошибка загрузки данных: " + QString::fromStdString(e.what()));
    } catch (const std::exception& e) {
        showError("Ошибка: " + QString::fromStdString(e.what()));
    }
}

void MainWindow::refreshVehicleTable() {
    vehicleTable->setRowCount(0);
    
    QString brandFilter = filterBrand->text().toLower();
    QString modelFilter = filterModel->text().toLower();
    int statusFilter = filterStatus->currentData().toInt();
    int typeFilter = filterType->currentData().toInt();
    
    int row = 0;
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        Vehicle* vehicle = *it;
        
        // Применить фильтры
        QString vehicleBrand = QString::fromStdString(vehicle->getBrand()).toLower();
        QString vehicleModel = QString::fromStdString(vehicle->getModel()).toLower();
        
        if (!brandFilter.isEmpty() && 
            vehicleBrand.indexOf(brandFilter) == -1) {
            continue;
        }
        if (!modelFilter.isEmpty() && 
            vehicleModel.indexOf(modelFilter) == -1) {
            continue;
        }
        if (statusFilter != -1 && 
            static_cast<int>(vehicle->getStatus()) != statusFilter) {
            continue;
        }
        
        TaxiVehicle* taxiVehicle = dynamic_cast<TaxiVehicle*>(vehicle);
        if (taxiVehicle) {
            if (typeFilter != -1 && 
                static_cast<int>(taxiVehicle->getVehicleType()) != typeFilter) {
                continue;
            }
        }
        
        vehicleTable->insertRow(row);
        QTableWidgetItem* idItem = new QTableWidgetItem(QString::number(row + 1));
        idItem->setData(Qt::UserRole, vehicle->getId());
        vehicleTable->setItem(row, 0, idItem);
        vehicleTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(vehicle->getBrand())));
        vehicleTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(vehicle->getModel())));
        vehicleTable->setItem(row, 3, new QTableWidgetItem(QString::number(vehicle->getYear())));
        vehicleTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(vehicle->getLicensePlate())));
        vehicleTable->setItem(row, 5, new QTableWidgetItem(QString::number(vehicle->getMileage())));
        vehicleTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(vehicle->getStatusString())));
        
        if (taxiVehicle) {
            vehicleTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(taxiVehicle->getVehicleTypeString())));
            vehicleTable->setItem(row, 8, new QTableWidgetItem(QString::number(taxiVehicle->getSeats())));
        } else {
            vehicleTable->setItem(row, 7, new QTableWidgetItem("Неизвестно"));
            vehicleTable->setItem(row, 8, new QTableWidgetItem("-"));
        }
        
        // Выделить если требуется техническое обслуживание
        if (vehicle->needsMaintenance()) {
            for (int col = 0; col < vehicleTable->columnCount(); ++col) {
                vehicleTable->item(row, col)->setBackground(Qt::yellow);
            }
        }
        
        row++;
    }
    
    statusLabel->setText(QString("Всего автомобилей: %1").arg(row));
}

void MainWindow::onAddVehicle() {
    historyManager.saveState(vehicles, "Добавление автомобиля");
    updateUndoRedoButtons();
    showVehicleForm();
}

void MainWindow::onEditVehicle() {
    Vehicle* vehicle = getSelectedVehicle();
    if (vehicle) {
        historyManager.saveState(vehicles, "Редактирование автомобиля");
        updateUndoRedoButtons();
        showVehicleForm(vehicle);
    } else {
        showError("Выберите автомобиль для редактирования");
    }
}

void MainWindow::onDeleteVehicle() {
    Vehicle* vehicle = getSelectedVehicle();
    if (!vehicle) {
        showError("Выберите автомобиль для удаления");
        return;
    }
    
    int ret = QMessageBox::question(this, "Подтверждение", 
                                     "Вы уверены, что хотите удалить этот автомобиль?",
                                     QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        try {
            historyManager.saveState(vehicles, "Удаление автомобиля");
            updateUndoRedoButtons();
            
            int vehicleId = vehicle->getId();
            
            // Удалить из списка
            for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
                if (*it == vehicle) {
                    vehicles.erase(it);
                    break;
                }
            }
            
            // Удалить из файла
            fileManager.deleteVehicle(vehicleId);
            delete vehicle;
            
            refreshVehicleTable();
            logOperation("Автомобиль удален: ID " + QString::number(vehicleId));
            showInfo("Автомобиль успешно удален");
        } catch (const TaxiParkException& e) {
            showError("Ошибка удаления: " + QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onRefreshVehicles() {
    refreshVehicleTable();
}

void MainWindow::onFilterChanged() {
    refreshVehicleTable();
}

void MainWindow::onViewOrders() {
    OrdersWindow* ordersWindow = new OrdersWindow(&orders, &vehicles, &fileManager, this);
    ordersWindow->setAttribute(Qt::WA_DeleteOnClose);
    ordersWindow->show();
}

void MainWindow::onAddOrder() {
    if (vehicles.empty()) {
        showError("Нет доступных автомобилей");
        return;
    }
    
    OrdersWindow* ordersWindow = new OrdersWindow(&orders, &vehicles, &fileManager, this);
    ordersWindow->setAttribute(Qt::WA_DeleteOnClose);
    ordersWindow->showAddOrderForm();
    ordersWindow->show();
}

void MainWindow::onViewStatistics() {
    StatisticsWindow* statsWindow = new StatisticsWindow(&vehicles, &orders, this);
    statsWindow->setAttribute(Qt::WA_DeleteOnClose);
    statsWindow->show();
}

void MainWindow::onViewOrdersCalendar() {
    OrdersCalendarWindow* calendarWindow = new OrdersCalendarWindow(&orders, &vehicles, this);
    calendarWindow->setAttribute(Qt::WA_DeleteOnClose);
    calendarWindow->show();
}

void MainWindow::onLoadData() {
    int ret = QMessageBox::question(this, "Подтверждение", 
                                     "Загрузить данные из файлов? Текущие данные будут заменены.",
                                     QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        try {
            // Очистить текущие данные
            for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
                delete *it;
            }
            vehicles.clear();
            orders.clear();
            
            // Загрузить из файлов
            List<Vehicle*> loadedVehicles = fileManager.loadAllVehicles();
            for (auto it = loadedVehicles.begin(); it != loadedVehicles.end(); ++it) {
                vehicles.push_back(*it);
            }
            orders = fileManager.loadOrders();
            
            refreshVehicleTable();
            historyManager.clear();
            updateUndoRedoButtons();
            logOperation(QString("Данные загружены из файлов: автомобилей %1, заказов %2")
                        .arg(vehicles.size())
                        .arg(orders.size()));
            showInfo(QString("Загружено автомобилей: %1, заказов: %2")
                    .arg(vehicles.size())
                    .arg(orders.size()));
        } catch (const TaxiParkException& e) {
            showError("Ошибка загрузки данных: " + QString::fromStdString(e.what()));
        } catch (const std::exception& e) {
            showError("Ошибка: " + QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onSaveData() {
    try {
        // Сохранить все транспортные средства
        for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
            fileManager.saveVehicle(*it);
        }
        
        // Сохранить заказы
        fileManager.saveOrders(orders);
        
        logOperation("Данные сохранены");
        showInfo("Данные успешно сохранены");
    } catch (const TaxiParkException& e) {
        showError("Ошибка сохранения: " + QString::fromStdString(e.what()));
    }
}

void MainWindow::showVehicleForm(Vehicle* vehicle) {
    VehicleForm form(vehicle, &vehicles, &fileManager, this);
    if (form.exec() == QDialog::Accepted) {
        refreshVehicleTable();
        updateUndoRedoButtons();
        if (vehicle) {
            logOperation("Автомобиль отредактирован: ID " + QString::number(vehicle->getId()));
        } else {
            logOperation("Автомобиль добавлен");
        }
    }
}

Vehicle* MainWindow::getSelectedVehicle() {
    int row = vehicleTable->currentRow();
    if (row < 0) {
        return nullptr;
    }
    
    QTableWidgetItem* idItem = vehicleTable->item(row, 0);
    if (!idItem) {
        return nullptr;
    }
    
    // Получить реальный идентификатор из UserRole
    QVariant idVariant = idItem->data(Qt::UserRole);
    int id;
    if (idVariant.isValid() && !idVariant.isNull()) {
        id = idVariant.toInt();
    } else {
        // Резервный вариант - использовать текст, если UserRole не установлен (для обратной совместимости)
        id = idItem->text().toInt();
    }
    
    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        if ((*it)->getId() == id) {
            return *it;
        }
    }
    
    return nullptr;
}

void MainWindow::showError(const QString& message) {
    QMessageBox::critical(this, "Ошибка", message);
    statusLabel->setText("Ошибка: " + message);
}

void MainWindow::showInfo(const QString& message) {
    QMessageBox::information(this, "Информация", message);
    statusLabel->setText(message);
}

void MainWindow::logOperation(const QString& operation) {
    QString logMessage = QString("[%1] %2")
                         .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                         .arg(operation);
    statusLabel->setText(logMessage);
}

void MainWindow::onUndo() {
    if (!historyManager.canUndo()) {
        return;
    }
    
    try {
        vehicles = historyManager.undo(vehicles);
        refreshVehicleTable();
        updateUndoRedoButtons();
        std::string desc = historyManager.getUndoDescription();
        logOperation("Отменено: " + QString::fromStdString(desc));
    } catch (const std::exception& e) {
        showError("Ошибка отмены: " + QString::fromStdString(e.what()));
    }
}

void MainWindow::onRedo() {
    if (!historyManager.canRedo()) {
        return;
    }
    
    try {
        vehicles = historyManager.redo(vehicles);
        refreshVehicleTable();
        updateUndoRedoButtons();
        std::string desc = historyManager.getRedoDescription();
        logOperation("Повторено: " + QString::fromStdString(desc));
    } catch (const std::exception& e) {
        showError("Ошибка повтора: " + QString::fromStdString(e.what()));
    }
}

void MainWindow::updateUndoRedoButtons() {
    btnUndo->setEnabled(historyManager.canUndo());
    btnRedo->setEnabled(historyManager.canRedo());
    
    if (historyManager.canUndo()) {
        std::string desc = historyManager.getUndoDescription();
        btnUndo->setToolTip(QString::fromStdString("Отменить: " + desc));
    } else {
        btnUndo->setToolTip("Нет действий для отмены");
    }
    
    if (historyManager.canRedo()) {
        std::string desc = historyManager.getRedoDescription();
        btnRedo->setToolTip(QString::fromStdString("Повторить: " + desc));
    } else {
        btnRedo->setToolTip("Нет действий для повтора");
    }
}

