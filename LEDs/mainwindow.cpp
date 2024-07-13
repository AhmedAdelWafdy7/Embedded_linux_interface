#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cp2112 = new GPIO("/dev/gpiochip0");
    if (!cp2112->isValid()) {
        QMessageBox::critical(this, "GPIO Initialization Error", "Failed to initialize GPIO. Please check the device.");
        // Consider disabling UI or closing the application if critical
    }
}

MainWindow::~MainWindow()
{
    delete cp2112;
    cp2112 = nullptr; // Good practice to nullify pointers after deletion
    delete ui;
}

void MainWindow::on_Led1_stateChanged(int boxState)
{
    if (cp2112) {
        try {
            cp2112->setLed1(boxState == Qt::Checked); // Assuming boxState is a checkbox state
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "LED1 Error", e.what());
        }
    }
}

void MainWindow::on_Led2_stateChanged(int boxState)
{
    if (cp2112) {
        try {
            cp2112->setLed2(boxState == Qt::Checked); // Correcting the logic to match Qt's checkbox state
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "LED2 Error", e.what());
        }
    }
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
    // Implementation depends on what needs to be done with the iconSize
}
