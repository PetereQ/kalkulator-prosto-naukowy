#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "input.h"
#include "strcalc.h"
#include <QShortcut>
#include <qevent.h>
#include <qimage.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QKeyEvent>
#include <QRegularExpressionValidator>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputBox->setReadOnly(false);
    ui->inputBox->setFocus();
    ui->inputBox->installEventFilter(this);


    this->output_state = EMPTY;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_inputBox_textChanged(const QString &arg1)
{
    ui->resultBox->setText(calculate(arg1, this->output_state));
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

void MainWindow::on_ctgButton_clicked()
{
    ui->inputBox->insert("ctg(");
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
    ui->inputBox->insert("sqrt(");
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
    ui->inputBox->insert("root(,"); // moze a√b?, bo jakby bylo a razy √b to by bylo a*√b, wiec sie nie pomyli
    // trzeba by bylo dodac przycisk przecinka ale na ogol działa
}

void MainWindow::on_percentButton_clicked()
{
    ui->inputBox->insert("%");
}

void MainWindow::on_open_brac_clicked()
{
    ui->inputBox->insert("(");
}

void MainWindow::on_close_brac_clicked()
{
    ui->inputBox->insert(")");
}

void MainWindow::handleFunction(int funcNumber, const QString &fileName, const QString &insertText)
{
    QFile file(fileName);
    QString content;

    // próba odczytu pliku
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        content = in.readAll();
        file.close();
    }

    if (content.contains("="))
    {
        // jeśli plik zawiera "="
        ui->inputBox->insert(insertText);
    }
    else if (!content.isEmpty())
    {
        // jeśli plik nie zawiera "=", ale nie jest pusty
        ui->inputBox->insert(insertText);

        F = funcNumber;
        Input *nw = new Input(F, this);

        // ustawiamy zawartość pliku w polu input_input
        nw->setInputText(content);

        nw->show();
    }
    else
    {
        // plik pusty
        F = funcNumber;
        Input *nw = new Input(F, this);
        nw->show();
    }
}

void MainWindow::on_func_1_clicked()
{
    handleFunction(1, "Fun1.txt", "fun1(");
}

void MainWindow::on_func_2_clicked()
{
    handleFunction(2, "Fun2.txt", "fun2(");
}

void MainWindow::on_func_3_clicked()
{
    handleFunction(3, "Fun3.txt", "fun3(");
}

void MainWindow::on_binButton_clicked()
{
    // 1. Pobierz tekst z pola wpisywania
    QString input = ui->inputBox->text();

    bool ok;
    // 2. Spróbuj zamienić tekst na liczbę całkowitą (LongLong mieści duże liczby)
    qlonglong number = input.toLongLong(&ok);

    if (ok)
    {
        output_state = BINARY;
        // 3. Jeśli się udało, zamień liczbę na system binarny (baza 2)
        QString binary = QString::number(number, 2);

        // 4. Wyświetl wynik w polu wyniku
        ui->resultBox->setText(binary);
    }
    else
    {
        this->output_state = ERROR;
        ui->resultBox->setText("Błąd: Wpisz jedną liczbę całkowitą");
    }
}
void MainWindow::on_clearButton_clicked()
{
    ui->inputBox->clear();
    ui->resultBox->clear();
}

// --- CYFERKI ---

void MainWindow::on_zeroButton_clicked() { ui->inputBox->insert("0"); }
void MainWindow::on_oneButton_clicked() { ui->inputBox->insert("1"); }
void MainWindow::on_twoButton_clicked() { ui->inputBox->insert("2"); }
void MainWindow::on_threeButton_clicked() { ui->inputBox->insert("3"); }
void MainWindow::on_fourButton_clicked() { ui->inputBox->insert("4"); }
void MainWindow::on_fiveButton_clicked() { ui->inputBox->insert("5"); }
void MainWindow::on_sixButton_clicked() { ui->inputBox->insert("6"); }
void MainWindow::on_sevenButton_clicked() { ui->inputBox->insert("7"); }
void MainWindow::on_eightButton_clicked() { ui->inputBox->insert("8"); }
void MainWindow::on_nineButton_clicked() { ui->inputBox->insert("9"); }

void MainWindow::on_commaButton_clicked()
{
    ui->inputBox->insert(".");
}

void MainWindow::on_equalsButton_clicked()
{
    if (this->output_state == RESULT)
    {
        double result;
        // oblicz wynik
        validate_and_eval(ui->inputBox->text().toStdString().c_str(), &result);
        std::string res_str = std::to_string(result);
        int i;
        // utnij zera z końca
        if (res_str.find(".") != std::string::npos)
        {
            for (i = res_str.size() - 1; i > 0 && (res_str[i] == '0' || res_str[i] == '.'); i--)
            {
            }
            res_str.resize(i + 1);
        }
        // ustaw wynik jako wejście
        ui->inputBox->setText(QString::fromStdString(res_str));
    }
}

void MainWindow::on_deleteButton_clicked()
{
    ui->inputBox->setFocus();
    ui->inputBox->backspace();
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->inputBox && event->type() == QEvent::KeyPress) {
        QKeyEvent *k = static_cast<QKeyEvent*>(event);
        int key = k->key();
        Qt::KeyboardModifiers mod = k->modifiers();

        if (key == Qt::Key_Left || key == Qt::Key_Right ||
            key == Qt::Key_Home || key == Qt::Key_End) {
            return false;
        }

        QPushButton *btn = nullptr;

        if (key == Qt::Key_0) btn = ui->zeroButton;
        else if (key == Qt::Key_1) btn = ui->oneButton;
        else if (key == Qt::Key_2) btn = ui->twoButton;
        else if (key == Qt::Key_3) btn = ui->threeButton;
        else if (key == Qt::Key_4) btn = ui->fourButton;
        else if (key == Qt::Key_5) btn = ui->fiveButton;
        else if (key == Qt::Key_6) btn = ui->sixButton;
        else if (key == Qt::Key_7) btn = ui->sevenButton;
        else if (key == Qt::Key_8) btn = ui->eightButton;
        else if (key == Qt::Key_9) btn = ui->nineButton;

        else if (key == Qt::Key_Plus) btn = ui->addButton;
        else if (key == Qt::Key_Minus) btn = ui->substractButton;
        else if (key == Qt::Key_Asterisk || key == Qt::Key_X) btn = ui->multiplicateButton; // * lub x
        else if (key == Qt::Key_Slash) btn = ui->divideButton;
        else if (key == Qt::Key_Percent) btn = ui->percentButton;

        else if (key == Qt::Key_ParenLeft) btn = ui->open_brac;
        else if (key == Qt::Key_ParenRight) btn = ui->close_brac;

        else if (key == Qt::Key_Return || key == Qt::Key_Enter || key == Qt::Key_Equal) btn = ui->equalsButton;

        else if (key == Qt::Key_Backspace) btn = ui->deleteButton;
        else if (key == Qt::Key_Delete) btn = ui->deleteButton;
        else if (key == Qt::Key_Escape) btn = ui->clearButton;

        else if (key == Qt::Key_Period || key == Qt::Key_Comma) btn = ui->commaButton;

        // P -> Kwadrat (^2)
        else if (key == Qt::Key_P) {
            btn = ui->squareButton;
        }

        // ^ -> Potęgowanie (Shift+6 lub sam daszek)
        else if (key == Qt::Key_AsciiCircum || (key == Qt::Key_6 && (mod & Qt::ShiftModifier))) {
            btn = ui->powerButton;
        }

        // R -> Piewiastek n-tego stopnia
        else if (key == Qt::Key_R) {
            btn = ui->rootButton;
        }


        // S -> Sinus / Sqrt
        else if (key == Qt::Key_S) {
            if (mod & Qt::ShiftModifier) btn = ui->sqrtButton; // Shift+S -> Pierwiastek
            else btn = ui->sinButton;                          // S -> Sinus
        }

        // T -> Tangens / Cotangens
        else if (key == Qt::Key_T) {
            if (mod & Qt::ShiftModifier) btn = ui->ctgButton;  // Shift+T -> Cotangens
            else btn = ui->tanButton;                          // T -> Tangens
        }

        // C -> Cosinus
        else if (key == Qt::Key_C) {
            btn = ui->cosButton;
        }

        // L -> Logarytmy
        else if (key == Qt::Key_L) {
            if (mod & Qt::ShiftModifier) btn = ui->lnButton;   // Shift+L -> Naturalny
            else btn = ui->logButton;                          // L -> Dziesiętny
        }

        // B -> Binarny
        else if (key == Qt::Key_B && (mod & Qt::ShiftModifier)) {
            btn = ui->binButton;
        }

        // F1, F2, F3
        else if (key == Qt::Key_F1) btn = ui->func_1;
        else if (key == Qt::Key_F2) btn = ui->func_2;
        else if (key == Qt::Key_F3) btn = ui->func_3; // (Upewnij się, że masz ten przycisk w .ui!)


        if (btn != nullptr) {
            btn->animateClick();
            return true;
        }

        if (k->matches(QKeySequence::Copy)) return false;

        return true;
    }


    return QMainWindow::eventFilter(watched, event);
}
