#include "StatisticsWindow.h"
#include "../vehicles/TaxiVehicle.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidgetItem>
#include <map>

StatisticsWindow::StatisticsWindow(List<Vehicle*>* vehicles, OrderList* orders, QWidget* parent)
    : QDialog(parent), vehicles(vehicles), orders(orders) {
    setupUI();
    calculateStatistics();
}

StatisticsWindow::~StatisticsWindow() {
}

void StatisticsWindow::setupUI() {
    setWindowTitle("📊 Статистика таксопарка");
    setMinimumSize(800, 600);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Общая статистика
    QGroupBox* summaryGroup = new QGroupBox("📈 Общая статистика", this);
    QVBoxLayout* summaryLayout = new QVBoxLayout(summaryGroup);

    totalVehiclesLabel = new QLabel(this);
    totalVehiclesLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    summaryLayout->addWidget(totalVehiclesLabel);

    onLineLabel = new QLabel(this);
    summaryLayout->addWidget(onLineLabel);

    inParkLabel = new QLabel(this);
    summaryLayout->addWidget(inParkLabel);

    inRepairLabel = new QLabel(this);
    summaryLayout->addWidget(inRepairLabel);

    totalOrdersLabel = new QLabel(this);
    summaryLayout->addWidget(totalOrdersLabel);

    needsMaintenanceLabel = new QLabel(this);
    needsMaintenanceLabel->setStyleSheet("font-size: 13px; font-weight: bold; color: black;");
    summaryLayout->addWidget(needsMaintenanceLabel);

    mainLayout->addWidget(summaryGroup);

    // Таблица детальной статистики
    QGroupBox* detailsGroup = new QGroupBox("📋 Статистика по типам ТС", this);
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsGroup);

    statsTable = new QTableWidget(this);
    statsTable->setColumnCount(6);
    statsTable->setHorizontalHeaderLabels({"Тип ТС", "Количество", "На линии", "В ремонте", "Всего мест", "Среднее мест"});
    statsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    statsTable->horizontalHeader()->setStretchLastSection(true);
    statsTable->setAlternatingRowColors(true);
    statsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    statsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    detailsLayout->addWidget(statsTable);

    mainLayout->addWidget(detailsGroup);
    
    // Добавить кнопку закрытия
    QPushButton* closeButton = new QPushButton("Закрыть", this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeButton);
}

void StatisticsWindow::calculateStatistics() {
    int total = 0;
    int onLine = 0;
    int inPark = 0;
    int inRepair = 0;
    int needsMaintenance = 0;
    int totalSeats = 0;

    std::map<std::string, int> typeCount;
    std::map<std::string, int> typeOnLine;
    std::map<std::string, int> typeInRepair;
    std::map<std::string, int> typeTotalSeats;
    std::map<std::string, int> typeSeatsCount;

    for (auto it = vehicles->begin(); it != vehicles->end(); ++it) {
        Vehicle* v = *it;
        total++;

        switch (v->getStatus()) {
            case VehicleStatus::ON_LINE:
                onLine++;
                break;
            case VehicleStatus::IN_PARK:
                inPark++;
                break;
            case VehicleStatus::IN_REPAIR:
                inRepair++;
                break;
        }

        if (v->needsMaintenance()) {
            needsMaintenance++;
        }

        TaxiVehicle* tv = dynamic_cast<TaxiVehicle*>(v);
        if (tv) {
            std::string type = tv->getVehicleTypeString();
            typeCount[type]++;
            int seats = tv->getSeats();
            typeTotalSeats[type] += seats;
            typeSeatsCount[type]++;
            totalSeats += seats;
            
            if (v->getStatus() == VehicleStatus::ON_LINE) {
                typeOnLine[type]++;
            }
            if (v->getStatus() == VehicleStatus::IN_REPAIR) {
                typeInRepair[type]++;
            }
        }
    }

    totalVehiclesLabel->setText(QString("🚗 Всего автомобилей: %1").arg(total));
    onLineLabel->setText(QString("✅ На линии: %1").arg(onLine));
    inParkLabel->setText(QString("🅿️ В парке: %1").arg(inPark));
    inRepairLabel->setText(QString("🔧 В ремонте: %1").arg(inRepair));
    totalOrdersLabel->setText(QString("📋 Всего заказов: %1").arg(orders->size()));
    needsMaintenanceLabel->setText(QString("⚠️ Требуют ТО: %1 | 💺 Всего мест: %2").arg(needsMaintenance).arg(totalSeats));

    // Заполнить таблицу
    statsTable->setRowCount(typeCount.size());
    int row = 0;
    for (const auto& pair : typeCount) {
        std::string type = pair.first;
        int count = pair.second;
        int totalSeatsForType = typeTotalSeats[type];
        double avgSeats = (typeSeatsCount[type] > 0) ? 
            static_cast<double>(totalSeatsForType) / typeSeatsCount[type] : 0.0;
        
        QTableWidgetItem* typeItem = new QTableWidgetItem(QString::fromStdString(type));
        typeItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        statsTable->setItem(row, 0, typeItem);
        
        QTableWidgetItem* countItem = new QTableWidgetItem(QString::number(count));
        countItem->setTextAlignment(Qt::AlignCenter);
        statsTable->setItem(row, 1, countItem);
        
        QTableWidgetItem* onLineItem = new QTableWidgetItem(QString::number(typeOnLine[type]));
        onLineItem->setTextAlignment(Qt::AlignCenter);
        statsTable->setItem(row, 2, onLineItem);
        
        QTableWidgetItem* inRepairItem = new QTableWidgetItem(QString::number(typeInRepair[type]));
        inRepairItem->setTextAlignment(Qt::AlignCenter);
        statsTable->setItem(row, 3, inRepairItem);
        
        QTableWidgetItem* totalSeatsItem = new QTableWidgetItem(QString::number(totalSeatsForType));
        totalSeatsItem->setTextAlignment(Qt::AlignCenter);
        statsTable->setItem(row, 4, totalSeatsItem);
        
        QTableWidgetItem* avgSeatsItem = new QTableWidgetItem(QString::number(avgSeats, 'f', 1));
        avgSeatsItem->setTextAlignment(Qt::AlignCenter);
        statsTable->setItem(row, 5, avgSeatsItem);
        
        row++;
    }
    
    // Изменить размер столбцов по содержимому
    statsTable->resizeColumnsToContents();
    
    // Установить минимальную ширину столбцов
    for (int col = 0; col < statsTable->columnCount(); ++col) {
        int width = statsTable->columnWidth(col);
        statsTable->setColumnWidth(col, qMax(width, 80));
    }
}

