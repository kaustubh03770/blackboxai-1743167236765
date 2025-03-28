#include "patient.h"
#include "ui_patientform.h"
#include "database.h"
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>

PatientManager::PatientManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientForm)
    , m_patientModel(new QSqlTableModel(this))
{
    ui->setupUi(this);
    setupModel();
    setupUi();
    refreshPatientList();
}

PatientManager::~PatientManager()
{
    delete ui;
    delete m_patientModel;
}

void PatientManager::setupModel()
{
    m_patientModel->setTable("patients");
    m_patientModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    m_patientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    m_patientModel->setHeaderData(2, Qt::Horizontal, tr("Date of Birth"));
    m_patientModel->setHeaderData(3, Qt::Horizontal, tr("Contact"));
}

void PatientManager::setupUi()
{
    ui->tableView->setModel(m_patientModel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->hideColumn(0); // Hide ID column
    ui->tableView->resizeColumnsToContents();

    connect(ui->addButton, &QPushButton::clicked, this, &PatientManager::onAddPatient);
    connect(ui->editButton, &QPushButton::clicked, this, &PatientManager::onEditPatient);
    connect(ui->deleteButton, &QPushButton::clicked, this, &PatientManager::onDeletePatient);
    connect(ui->searchButton, &QPushButton::clicked, this, &PatientManager::onSearchPatient);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &PatientManager::onPatientSelected);
}

void PatientManager::refreshPatientList()
{
    if (!m_patientModel->select()) {
        QMessageBox::critical(this, tr("Error"), 
                            tr("Failed to load patients: %1").arg(m_patientModel->lastError().text()));
    }
}

void PatientManager::onAddPatient()
{
    QSqlRecord record = m_patientModel->record();
    record.setValue("name", ui->nameEdit->text());
    record.setValue("dob", ui->dobEdit->text());
    record.setValue("contact", ui->contactEdit->text());
    
    if (m_patientModel->insertRecord(-1, record)) {
        if (m_patientModel->submitAll()) {
            refreshPatientList();
            ui->nameEdit->clear();
            ui->dobEdit->clear();
            ui->contactEdit->clear();
        } else {
            QMessageBox::critical(this, tr("Error"), 
                                tr("Failed to add patient: %1").arg(m_patientModel->lastError().text()));
        }
    }
}

void PatientManager::onEditPatient()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    m_patientModel->setData(m_patientModel->index(index.row(), 1), ui->nameEdit->text());
    m_patientModel->setData(m_patientModel->index(index.row(), 2), ui->dobEdit->text());
    m_patientModel->setData(m_patientModel->index(index.row(), 3), ui->contactEdit->text());

    if (!m_patientModel->submitAll()) {
        QMessageBox::critical(this, tr("Error"), 
                            tr("Failed to update patient: %1").arg(m_patientModel->lastError().text()));
    }
}

void PatientManager::onDeletePatient()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (!index.isValid()) return;

    if (QMessageBox::question(this, tr("Confirm Delete"),
                            tr("Are you sure you want to delete this patient?")) == QMessageBox::Yes) {
        m_patientModel->removeRow(index.row());
        if (!m_patientModel->submitAll()) {
            QMessageBox::critical(this, tr("Error"), 
                                tr("Failed to delete patient: %1").arg(m_patientModel->lastError().text()));
        }
        refreshPatientList();
    }
}

void PatientManager::onSearchPatient()
{
    QString name = ui->searchEdit->text();
    if (name.isEmpty()) {
        m_patientModel->setFilter("");
    } else {
        m_patientModel->setFilter(QString("name LIKE '%%1%'").arg(name));
    }
    refreshPatientList();
}

void PatientManager::onPatientSelected(const QModelIndex &index)
{
    if (index.isValid()) {
        ui->nameEdit->setText(m_patientModel->record(index.row()).value("name").toString());
        ui->dobEdit->setText(m_patientModel->record(index.row()).value("dob").toString());
        ui->contactEdit->setText(m_patientModel->record(index.row()).value("contact").toString());
    }
}