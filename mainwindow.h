#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_inputBox_textChanged(const QString &arg1);

    void on_addButton_clicked();

    void on_substractButton_clicked();

    void on_multiplicateButton_clicked();

    void on_divideButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
