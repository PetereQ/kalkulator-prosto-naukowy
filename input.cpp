#include "input.h"
#include "ui_input.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Input::Input(int fValue, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Input)
    , F(fValue)
{
    ui->setupUi(this);
}

Input::~Input()
{
    delete ui;
}

void Input::on_ok_input_clicked()
{
    QString filename = "";
    switch (F)
    {
    case 1:
        filename = "Fun1.txt";
        break;
    case 2:
        filename = "Fun2.txt";
        break;
    case 3:
        filename = "Fun3.txt";
        break;
    default:
        qDebug() << "Zly rodzaj funkcji, zmiennej F";
        break;
    }

    QFile file(filename);

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

