#include "input.h"
#include "ui_input.h"
#include <qevent.h>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <Windows.h>

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
    // QString inputText = ui->input_input->text();
    // QFile file("Functions.txt");
    // QStringList lines;

    // if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    // {
    //     QTextStream in(&file);
    //     while (!in.atEnd())
    //         lines.append(in.readLine());
    //     file.close();
    // }

    // // while (lines.size() < 2)
    // //     lines.append("");

    // lines[1] = inputText;

    // if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    // {
    //     QTextStream out(&file);
    //     for (const QString &line : lines)
    //         out << line << "\n";
    //     file.close();
    // }
    Input::~Input();
}

void Input::on_cancel_input_clicked()
{
    Input::~Input();
    this->close();

}

void Input::on_input_input(const QString &arg1)
{
    // obsługa wpisanego tekstu
}
