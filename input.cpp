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
    QFile file("Functions.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Nie znaleziono pliku";
        return;
    }

    QTextStream out(&file);
    out << inputText << "\n";

    qDebug() << inputText;
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

    //qDebug() << inputText;
}

