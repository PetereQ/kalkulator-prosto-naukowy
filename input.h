#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QString>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    void setInputText(const QString &text); // setter do pola input_input
    explicit Input(int fValue, QWidget *parent = nullptr);
    ~Input();

private slots:
    void on_input_input_textChanged(const QString &arg1);
    void on_ok_input_clicked();
    void on_cancel_input_clicked();

private:
    Ui::Input *ui;
    QString inputText;
    int F;
};

#endif // INPUT_H
