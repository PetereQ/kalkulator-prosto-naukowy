#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "strcalc.h"
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_calculator(new StrCalc())
{
    ui->setupUi(this);
    ui->inputBox->setReadOnly(true);

    QShortcut *dotShortcut = new QShortcut(QKeySequence("."), this);
    connect(dotShortcut, &QShortcut::activated, ui->commaButton, &QPushButton::animateClick);

    QShortcut *returnShortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(returnShortcut, &QShortcut::activated, ui->equalsButton, &QPushButton::animateClick);

    QShortcut *backspaceShortcut = new QShortcut(QKeySequence(Qt::Key_Backspace), this);
    connect(backspaceShortcut, &QShortcut::activated, ui->deleteButton, &QPushButton::animateClick);
}

class MainWindowPrivate {
public:
    StrCalc calculator;
};

MainWindow::~MainWindow()
{
    delete m_calculator;
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
    ui->inputBox->insert("root(");
    QToolTip::showText(ui->rootButton->mapToGlobal(QPoint(0, -20)),
                      "root(stopień, liczba)\nPrzykład: root(3,8) dla ∛8",
                      ui->rootButton);
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


void MainWindow::on_func_1_clicked()
{
    ui->inputBox->insert("fun1(");
}

void MainWindow::on_func_2_clicked()
{
    ui->inputBox->insert("fun2(");
}

void MainWindow::on_func_3_clicked()
{
    ui->inputBox->insert("fun3(");
}

QString MainWindow::calculate(const QString &input) {
    if (input.isEmpty()) {
        return "";
    }
    if (m_calculator) {
        QString result = m_calculator->calculate(input);
        return result;
    }
    QJSEngine engine;
    QString expr = input;
    
    void MainWindow::on_sqrtButton_clicked()
{
    ui->inputBox->insert("sqrt(");
}
    expr.replace("^", "**");
    if (expr.contains("sin") || expr.contains("cos") || 
        expr.contains("tan") || expr.contains("ctg") ||
        expr.contains("log") || expr.contains("ln") ||
        expr.contains("sqrt") || expr.contains("root")) {
        return "Uzyj pelnego parsera (wlaczony)";
    }
    
    QJSValue result = engine.evaluate(expr);
    if (result.isError()) {
        return "Blad: " + result.toString();
    }
    return result.toString();
}


void MainWindow::on_binButton_clicked()
{
    QString input = ui->inputBox->text();

    bool ok;
    qlonglong number = input.toLongLong(&ok);

    if (ok) {
        QString binary = QString::number(number, 2);
        ui->resultBox->setText(binary);
    } else {
        ui->resultBox->setText("Blad: Wpisz jedna liczbe calkowita");
    }
}
void MainWindow::on_clearButton_clicked()
{
    ui->inputBox->clear();
    ui->resultBox->clear();
}


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
    ui->inputBox->setText(ui->resultBox->text());
}

void MainWindow::on_deleteButton_clicked()
{
    QString text = ui->inputBox->text();
    if (!text.isEmpty()) {
        text.chop(1);
        ui->inputBox->setText(text);
    }
}
