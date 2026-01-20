#include "input.h"
#include "ui_input.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


Input::Input(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Input)
{
    ui->setupUi(this);
}

Input::~Input()
{
    delete ui;
}

void Input::on_ok_input_clicked()
{
    QFile file("Fun1.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        qDebug() << "Blad z otwarciem pliku";
        return;
    }
    QTextStream out(&file);
    out << inputText << "\n";

    file.close();
    this->accept();
}


void Input::on_cancel_input_clicked()
{
    this->reject();
}

void Input::on_input_input_textChanged(const QString &arg1)
{
    inputText = arg1;
}

