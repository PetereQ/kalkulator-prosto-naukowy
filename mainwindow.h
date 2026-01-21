#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

typedef enum {
    EMPTY,
    RESULT,
    ERROR,
    BINARY
} OutputState;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    OutputState output_state;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputBox_textChanged(const QString &arg1);

    void on_addButton_clicked();

    void on_substractButton_clicked();

    void on_multiplicateButton_clicked();

    void on_divideButton_clicked();

    void on_sinButton_clicked();

    void on_cosButton_clicked();

    void on_tanButton_clicked();

    void on_ctgButton_clicked();

    void on_logButton_clicked();

    void on_lnButton_clicked();

    void on_sqrtButton_clicked();

    void on_squareButton_clicked();

    void on_powerButton_clicked();

    void on_rootButton_clicked();

    void on_percentButton_clicked();

    void on_binButton_clicked();

    void on_clearButton_clicked();

    void on_zeroButton_clicked();

    void on_oneButton_clicked();

    void on_twoButton_clicked();

    void on_threeButton_clicked();

    void on_fourButton_clicked();

    void on_fiveButton_clicked();

    void on_sixButton_clicked();

    void on_sevenButton_clicked();

    void on_eightButton_clicked();

    void on_nineButton_clicked();

    void on_commaButton_clicked();

    void on_equalsButton_clicked();

    void on_deleteButton_clicked();

    void on_close_brac_clicked();

    void on_open_brac_clicked();

    // Custom Functions:

    void on_func_1_clicked();

    void on_func_2_clicked();

    void on_func_3_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
