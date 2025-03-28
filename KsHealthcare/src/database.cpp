#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    // Set database path in application data directory
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDataPath);
    m_databasePath = appDataPath + "/kshealthcare.db";
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::connect()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_databasePath);
    
    if (!m_db.open()) {
        qCritical() << "Database connection error:" << m_db.lastError();
        return false;
    }

    if (!initializeDatabase()) {
        qCritical() << "Failed to initialize database";
        return false;
    }

    return true;
}

bool DatabaseManager::initializeDatabase()
{
    if (!m_db.tables().contains("patients")) {
        return createTables();
    }
    return true;
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    
    // Patients table
    if (!query.exec("CREATE TABLE patients ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT NOT NULL,"
                   "dob TEXT NOT NULL,"
                   "contact TEXT NOT NULL,"
                   "medical_history TEXT)")) {
        qCritical() << "Failed to create patients table:" << query.lastError();
        return false;
    }

    // Appointments table
    if (!query.exec("CREATE TABLE appointments ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "patient_id INTEGER NOT NULL,"
                   "date TEXT NOT NULL,"
                   "doctor TEXT NOT NULL,"
                   "notes TEXT,"
                   "FOREIGN KEY(patient_id) REFERENCES patients(id))")) {
        qCritical() << "Failed to create appointments table:" << query.lastError();
        return false;
    }

    // Billing table
    if (!query.exec("CREATE TABLE billing ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "patient_id INTEGER NOT NULL,"
                   "services TEXT NOT NULL,"
                   "amount REAL NOT NULL,"
                   "date TEXT NOT NULL,"
                   "status TEXT NOT NULL DEFAULT 'Pending',"
                   "FOREIGN KEY(patient_id) REFERENCES patients(id))")) {
        qCritical() << "Failed to create billing table:" << query.lastError();
        return false;
    }

    // Prescriptions table
    if (!query.exec("CREATE TABLE prescriptions ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "patient_id INTEGER NOT NULL,"
                   "medications TEXT NOT NULL,"
                   "instructions TEXT NOT NULL,"
                   "date TEXT NOT NULL,"
                   "FOREIGN KEY(patient_id) REFERENCES patients(id))")) {
        qCritical() << "Failed to create prescriptions table:" << query.lastError();
        return false;
    }

    return true;
}

QSqlError DatabaseManager::lastError() const
{
    return m_db.lastError();
}

// Patient operations implementation
bool DatabaseManager::addPatient(const QString &name, const QString &dob, const QString &contact)
{
    QSqlQuery query;
    query.prepare("INSERT INTO patients (name, dob, contact) VALUES (?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(dob);
    query.addBindValue(contact);
    return query.exec();
}

QList<QVariantMap> DatabaseManager::getAllPatients()
{
    QList<QVariantMap> patients;
    QSqlQuery query("SELECT * FROM patients ORDER BY name");
    
    while (query.next()) {
        QVariantMap patient;
        patient["id"] = query.value("id");
        patient["name"] = query.value("name");
        patient["dob"] = query.value("dob");
        patient["contact"] = query.value("contact");
        patients.append(patient);
    }
    
    return patients;
}

// Other CRUD operations would be implemented similarly
// ...