#ifndef INPUT_H
#define INPUT_H

#include <QDialog>

namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:

    explicit Input(QWidget *parent = nullptr);
    ~Input();

private slots:
    void on_input_input(const QString &arg1);

    void on_ok_input();
    void on_cancel_input();


private:
    Ui::Input *ui;
    QString inputText;
};

#endif // INPUT_H
