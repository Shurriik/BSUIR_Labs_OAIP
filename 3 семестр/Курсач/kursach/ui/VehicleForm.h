#ifndef VEHICLEFORM_H
#define VEHICLEFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include "../core/Vehicle.h"
#include "../core/List.h"
#include "../storage/FileManager.h"

class VehicleForm : public QDialog {
    Q_OBJECT

public:
    VehicleForm(Vehicle* vehicle, List<Vehicle*>* vehicles, FileManager* fileManager, QWidget* parent = nullptr);
    ~VehicleForm();

private slots:
    void onVehicleTypeChanged(int index);
    void onSave();
    void onCancel();

private:
    void setupUI();
    void loadVehicleData();
    void clearForm();
    bool validateInput();
    Vehicle* createVehicleFromForm();

    Vehicle* editingVehicle;
    List<Vehicle*>* vehicles;
    FileManager* fileManager;

    // Общие поля
    QLineEdit* brandEdit;
    QLineEdit* modelEdit;
    QSpinBox* yearSpin;
    QLineEdit* licensePlateEdit;
    QSpinBox* mileageSpin;
    QComboBox* statusCombo;
    QComboBox* vehicleTypeCombo;
    QSpinBox* seatsSpin;
    QLineEdit* categoryEdit;

    // Специфические поля
    QDoubleSpinBox* basePriceSpin;
    QCheckBox* climateControlCheck;
    QCheckBox* seatHeatingCheck;
    QCheckBox* seatMassageCheck;
    QCheckBox* navigationCheck;
    QCheckBox* cruiseControlCheck;
    QCheckBox* steeringWheelHeatingCheck;
    QCheckBox* leatherSeatsCheck;
    QCheckBox* premiumAudioCheck;
    QCheckBox* childSeatsCheck;
    QSpinBox* luggageCapacitySpin;

    QPushButton* saveButton;
    QPushButton* cancelButton;
};

#endif // VEHICLEFORM_H

