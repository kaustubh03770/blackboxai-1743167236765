#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dbManager(new DatabaseManager(this))
{
    setWindowTitle("Ks'Healthcare - Hospital Management System");
    resize(1024, 768);
    
    setupUi();
    createConnections();
    
    // Initialize database connection
    if (!dbManager->connect()) {
        // Handle connection error
    }
}

MainWindow::~MainWindow()
{
    delete dbManager;
}

void MainWindow::setupUi()
{
    // Main layout
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    
    // Navigation panel
    QWidget *navPanel = new QWidget;
    QVBoxLayout *navLayout = new QVBoxLayout(navPanel);
    
    patientsBtn = new QPushButton("Patients");
    appointmentsBtn = new QPushButton("Appointments");
    billingBtn = new QPushButton("Billing");
    prescriptionsBtn = new QPushButton("Prescriptions");
    
    navLayout->addWidget(patientsBtn);
    navLayout->addWidget(appointmentsBtn);
    navLayout->addWidget(billingBtn);
    navLayout->addWidget(prescriptionsBtn);
    navLayout->addStretch();
    
    // Content area
    stackedWidget = new QStackedWidget;
    
    // Add pages to stacked widget (to be implemented)
    stackedWidget->addWidget(new QLabel("Patients Module"));
    stackedWidget->addWidget(new QLabel("Appointments Module"));
    stackedWidget->addWidget(new QLabel("Billing Module"));
    stackedWidget->addWidget(new QLabel("Prescriptions Module"));
    
    mainLayout->addWidget(navPanel, 1);
    mainLayout->addWidget(stackedWidget, 4);
    
    setCentralWidget(centralWidget);
}

void MainWindow::createConnections()
{
    connect(patientsBtn, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(0);
    });
    connect(appointmentsBtn, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(1);
    });
    connect(billingBtn, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(2);
    });
    connect(prescriptionsBtn, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(3);
    });
}