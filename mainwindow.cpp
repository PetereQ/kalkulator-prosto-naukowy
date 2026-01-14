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

void MainWindow::on_sinButton_clicked()
{
    ui->inputBox->insert("sin(");
}

void MainWindow::on_cosButton_clicked()
{
    ui->inputBox->insert("cos(");
}

void MainWindow::on_tanButton_clicked()
{
    ui->inputBox->insert("tan(");
}

void MainWindow::on_logButton_clicked()
{
    ui->inputBox->insert("log(");
}

void MainWindow::on_lnButton_clicked()
{
    ui->inputBox->insert("ln(");
}

void MainWindow::on_sqrtButton_clicked()
{
    ui->inputBox->insert("√");
}

void MainWindow::on_squareButton_clicked()
{
    ui->inputBox->insert("^2");
}

void MainWindow::on_powerButton_clicked()
{
    ui->inputBox->insert("^");
}

void MainWindow::on_rootButton_clicked()
{
    // to nie wiem jak zrobić aby dobrze wygladalo i dzialalo
    ui->inputBox->insert("pierwsiatek stopnia a z b?");
}

void MainWindow::on_percentButton_clicked()
{
    ui->inputBox->insert("%");
}

void MainWindow::on_binButton_clicked()
{
    // 1. Pobierz tekst z pola wpisywania
    QString input = ui->inputBox->text();

    bool ok;
    // 2. Spróbuj zamienić tekst na liczbę całkowitą (LongLong mieści duże liczby)
    qlonglong number = input.toLongLong(&ok);

    if (ok) {
        // 3. Jeśli się udało, zamień liczbę na system binarny (baza 2)
        QString binary = QString::number(number, 2);

        // 4. Wyświetl wynik w polu wyniku
        ui->resultBox->setText(binary);
    } else {
        ui->resultBox->setText("Błąd: Wpisz jedną liczbę całkowitą");
    }
}
void MainWindow::on_clearButton_clicked()
{
    ui->inputBox->clear();
    ui->resultBox->clear();
}
