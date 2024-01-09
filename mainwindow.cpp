#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize variables
    currentFloor = 1;
    targetFloor = 1;
    elevator1CurrentFloor = 1;
    elevator2CurrentFloor = 1;

    // Connect signals and slots
    connect(ui->startingfloor, SIGNAL(currentIndexChanged(int)), this, SLOT(on_startingFloor_currentIndexChanged(int)));
    connect(ui->buttonUp, SIGNAL(clicked()), this, SLOT(on_buttonUp_clicked()));
    connect(ui->buttonDown, SIGNAL(clicked()), this, SLOT(on_buttonDown_clicked()));
    connect(ui->buttonFloor1, SIGNAL(clicked()), this, SLOT(on_buttonFloor1_clicked()));
    connect(ui->buttonFloor2, SIGNAL(clicked()), this, SLOT(on_buttonFloor2_clicked()));
    connect(ui->buttonFloor3, SIGNAL(clicked()), this, SLOT(on_buttonFloor3_clicked()));
    connect(ui->buttonFloor4, SIGNAL(clicked()), this, SLOT(on_buttonFloor4_clicked()));
    connect(ui->buttonFire, SIGNAL(clicked()), this, SLOT(on_buttonFire_clicked()));
    connect(ui->buttonObstacle, SIGNAL(clicked()), this, SLOT(on_buttonObstacle_clicked()));
    connect(ui->buttonOverload, SIGNAL(clicked()), this, SLOT(on_buttonOverload_clicked()));
    connect(ui->buttonPowerOutage, SIGNAL(clicked()), this, SLOT(on_buttonPowerOutage_clicked()));
    connect(ui->buttonHelp, SIGNAL(clicked()), this, SLOT(on_buttonHelp_clicked()));

    // Initialize elevator timer
    elevatorTimer = new QTimer(this);
    connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator1Display())); // Default to Elevator 1
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startingFloor_currentIndexChanged(int index)
{
    targetFloor = index + 1; // Since floor indices start from 0
}

void MainWindow::on_buttonUp_clicked()
{
    // Choose the nearest elevator and start moving towards the target floor
    int nearestElevator = (qAbs(elevator1CurrentFloor - targetFloor) < qAbs(elevator2CurrentFloor - targetFloor)) ? 1 : 2;
    qDebug() << "Button Up Clicked. Nearest elevator selected: " << nearestElevator;

    if (nearestElevator == 1) {
        elevatorTimer->disconnect();  // Disconnect the existing connection to avoid updating both elevators
        connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator1Display()));
    } else {
        elevatorTimer->disconnect();  // Disconnect the existing connection to avoid updating both elevators
        connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator2Display()));
    }

    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonDown_clicked()
{
    // Choose the nearest elevator and start moving towards the target floor
    int nearestElevator = (qAbs(elevator1CurrentFloor - targetFloor) < qAbs(elevator2CurrentFloor - targetFloor)) ? 1 : 2;
    qDebug() << "Button Down Clicked. Nearest elevator selected: " << nearestElevator;

    if (nearestElevator == 1) {
        elevatorTimer->disconnect();  // Disconnect the existing connection to avoid updating both elevators
        connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator1Display()));
    } else {
        elevatorTimer->disconnect();  // Disconnect the existing connection to avoid updating both elevators
        connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator2Display()));
    }

    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonFloor1_clicked()
{
    qDebug() << "Button Floor 1 Clicked.";
    targetFloor = 1;
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonFloor2_clicked()
{
    qDebug() << "Button Floor 2 Clicked.";
    targetFloor = 2;
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonFloor3_clicked()
{
    qDebug() << "Button Floor 3 Clicked.";
    targetFloor = 3;
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonFloor4_clicked()
{
    qDebug() << "Button Floor 4 Clicked.";
    targetFloor = 4;
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonFire_clicked()
{
    qDebug() << "FIRE! Elevator 1 and 2 are moving down to Floor 1.";
    targetFloor = 1;
    elevatorTimer->disconnect();  // Disconnect the existing connection to avoid updating both elevators
    connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator1DisplayEmergency()));
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
    connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator2DisplayEmergency()));
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}

void MainWindow::on_buttonObstacle_clicked()
{
    qDebug() << "Please remove obstacle for the elevator to move";
    // Implement obstacle scenario logic here
}

void MainWindow::on_buttonOverload_clicked()
{
    qDebug() << "Please lower the weight caused on the elevator";
    // Implement overload scenario logic here
}

void MainWindow::on_buttonPowerOutage_clicked()
{
    qDebug() << "There is a Power Outage the elevator is moving to the 1st floor.";
    targetFloor = 1;
    elevatorTimer->disconnect();  // Disconnect the existing connection to avoid updating both elevators
    connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator1DisplayEmergency()));
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
    connect(elevatorTimer, SIGNAL(timeout()), this, SLOT(updateElevator2DisplayEmergency()));
    elevatorTimer->start(1000); // Start the timer to update the display every 1 second
}
void MainWindow::on_buttonHelp_clicked(){
   qDebug() << "Connecting to Emergency Services.....";
}
void MainWindow::updateElevator1Display()
{
    // Update the elevator display and simulate moving towards the target floor for Elevator 1
    if (elevator1CurrentFloor < targetFloor) {
        elevator1CurrentFloor++;
    } else if (elevator1CurrentFloor > targetFloor) {
        elevator1CurrentFloor--;
    }

    ui->Elevator1->display(elevator1CurrentFloor);

    if (elevator1CurrentFloor == targetFloor) {
        elevatorTimer->stop(); // Stop the timer when Elevator 1 reaches the target floor
        qDebug() << "Elevator 1 reached the target floor.";
    }
}
void MainWindow::updateElevator1DisplayEmergency()
{
    // Update the elevator display and simulate moving towards the target floor for Elevator 1
    int safeFloor = 1;
    if (elevator1CurrentFloor > safeFloor) {
        elevator1CurrentFloor--;
    }

    ui->Elevator1->display(elevator1CurrentFloor);

    if (elevator1CurrentFloor == safeFloor) {
        elevatorTimer->stop(); // Stop the timer when Elevator 1 reaches the target floor
        qDebug() << "Elevator 1 reached the target floor.";
    }
}
void MainWindow::updateElevator2Display()
{
    // Update the elevator display and simulate moving towards the target floor for Elevator 2
    if (elevator2CurrentFloor < targetFloor) {
        elevator2CurrentFloor++;
    } else if (elevator2CurrentFloor > targetFloor) {
        elevator2CurrentFloor--;
    }

    ui->Elevator2->display(elevator2CurrentFloor);

    if (elevator2CurrentFloor == targetFloor) {
        elevatorTimer->stop(); // Stop the timer when Elevator 2 reaches the target floor
        qDebug() << "Elevator 2 reached the target floor.";
    }
}
void MainWindow::updateElevator2DisplayEmergency()
{
    // Update the elevator display and simulate moving towards the target floor for Elevator 1
    int safeFloor = 1;
    if (elevator2CurrentFloor > safeFloor) {
        elevator2CurrentFloor--;
    }

    ui->Elevator2->display(elevator2CurrentFloor);

    if (elevator2CurrentFloor == safeFloor) {
        elevatorTimer->stop(); // Stop the timer when Elevator 2 reaches the target floor
        qDebug() << "Elevator 2 reached the target floor.";
    }
}
