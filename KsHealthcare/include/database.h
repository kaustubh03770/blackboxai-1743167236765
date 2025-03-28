#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool connect();
    bool initializeDatabase();
    QSqlError lastError() const;

    // Patient operations
    bool addPatient(const QString &name, const QString &dob, const QString &contact);
    bool updatePatient(int id, const QString &name, const QString &dob, const QString &contact);
    bool deletePatient(int id);
    QList<QVariantMap> getAllPatients();

    // Appointment operations
    bool addAppointment(int patientId, const QString &date, const QString &doctor, const QString &notes);
    // ... other appointment operations

    // Billing operations
    bool addBill(int patientId, const QString &services, double amount);
    // ... other billing operations

    // Prescription operations
    bool addPrescription(int patientId, const QString &medications, const QString &instructions);
    // ... other prescription operations

private:
    QSqlDatabase m_db;
    QString m_databasePath;
    bool createTables();
};

#endif // DATABASE_H