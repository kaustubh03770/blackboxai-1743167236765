#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class QPushButton;
class DatabaseManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
    void createConnections();

    QStackedWidget *stackedWidget;
    DatabaseManager *dbManager;
    
    // Navigation buttons
    QPushButton *patientsBtn;
    QPushButton *appointmentsBtn;
    QPushButton *billingBtn;
    QPushButton *prescriptionsBtn;
};

#endif // MAINWINDOW_H