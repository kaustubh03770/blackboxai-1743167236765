cmake_minimum_required(VERSION 3.5)
project(KsHealthcare VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

# Process UI files
qt_add_resources(KsHealthcare_RESOURCES
    "resources"
    PREFIX
    "/"
    FILES
    resources/ks_logo.png
)

qt_wrap_ui(KsHealthcare_FORMS_HEADERS
    ui/patientform.ui
)

qt_add_executable(KsHealthcare
    src/main.cpp
    src/mainwindow.cpp
    src/database.cpp
    src/patient.cpp
    src/appointment.cpp
    src/billing.cpp
    src/prescription.cpp
    ${KsHealthcare_FORMS_HEADERS}
    ${KsHealthcare_RESOURCES}
)

target_link_libraries(KsHealthcare PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

include_directories(${CMAKE_SOURCE_DIR}/include)