cmake_minimum_required(VERSION 3.16)
project(TaxiPark VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable Qt MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/vehicles
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/storage
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

# Source files
set(CORE_SOURCES
    core/Vehicle.cpp
    core/Order.cpp
    core/HistoryManager.cpp
    core/OrderList.cpp
)

set(VEHICLE_SOURCES
    vehicles/TaxiVehicle.cpp
    vehicles/EconomyCar.cpp
    vehicles/ComfortCar.cpp
    vehicles/BusinessCar.cpp
    vehicles/Minivan.cpp
)

set(EXCEPTION_SOURCES
    exceptions/TaxiParkException.cpp
)

set(STORAGE_SOURCES
    storage/FileManager.cpp
)

set(UI_SOURCES
    ui/MainWindow.cpp
    ui/VehicleForm.cpp
    ui/OrdersWindow.cpp
    ui/OrderForm.cpp
    ui/StatisticsWindow.cpp
    ui/OrdersCalendarWindow.cpp
)

# Headers (for MOC)
set(UI_HEADERS
    ui/MainWindow.h
    ui/VehicleForm.h
    ui/OrdersWindow.h
    ui/OrderForm.h
    ui/StatisticsWindow.h
    ui/OrdersCalendarWindow.h
)

# Executable
add_executable(${PROJECT_NAME}
    main.cpp
    ${CORE_SOURCES}
    ${VEHICLE_SOURCES}
    ${EXCEPTION_SOURCES}
    ${STORAGE_SOURCES}
    ${UI_SOURCES}
    ${UI_HEADERS}
)

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
)

# Windows specific settings
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
    
    # Automatically copy Qt DLLs to build directory
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS ${Qt6_DIR}/../../../bin)
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Deploying Qt libraries..."
        )
    endif()
endif()

