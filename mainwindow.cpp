#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "strcalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputBox_textChanged(const QString &arg1)
{
    ui->resultBox->setText(calculate(arg1));
}


void MainWindow::on_addButton_clicked()
{
    ui->inputBox->insert("+");
}


void MainWindow::on_substractButton_clicked()
{

    ui->inputBox->insert("-");
}


void MainWindow::on_divideButton_clicked()
{

    ui->inputBox->insert("/");
}


void MainWindow::on_multiplicateButton_clicked()
{

    ui->inputBox->insert("*");
}

