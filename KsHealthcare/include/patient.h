#ifndef PATIENT_H
#define PATIENT_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class PatientForm;
}

class PatientManager : public QWidget
{
    Q_OBJECT

public:
    explicit PatientManager(QWidget *parent = nullptr);
    ~PatientManager();

private slots:
    void onAddPatient();
    void onEditPatient();
    void onDeletePatient();
    void onSearchPatient();
    void onPatientSelected(const QModelIndex &index);

private:
    Ui::PatientForm *ui;
    QSqlTableModel *m_patientModel;
    void setupModel();
    void setupUi();
    void refreshPatientList();
};

#endif // PATIENT_H