#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QString getPin() const;

private slots:
    void on_btn1_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btn0_clicked();

    void on_btnReset_clicked();

    void on_btnErase_clicked();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::Dialog *ui;
    QString correctPin = "1234";
    int attempts = 3;
    QString pin;
};

#endif // DIALOG_H
