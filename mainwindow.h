#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startingFloor_currentIndexChanged(int index);
    void on_buttonUp_clicked();
    void on_buttonDown_clicked();
    void on_buttonFloor1_clicked();
    void on_buttonFloor2_clicked();
    void on_buttonFloor3_clicked();
    void on_buttonFloor4_clicked();
    void on_buttonFire_clicked();
    void on_buttonObstacle_clicked();
    void on_buttonOverload_clicked();
    void on_buttonPowerOutage_clicked();
    void on_buttonHelp_clicked();
    void updateElevator1Display();
    void updateElevator1DisplayEmergency();
    void updateElevator2Display();
    void updateElevator2DisplayEmergency();

private:
    Ui::MainWindow *ui;
    QTimer *elevatorTimer;
    int currentFloor;
    int targetFloor;
    int elevator1CurrentFloor;
    int elevator2CurrentFloor;
};

#endif // MAINWINDOW_H
