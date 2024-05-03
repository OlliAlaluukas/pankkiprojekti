#ifndef VALITSE_H
#define VALITSE_H

#include <QDialog>
#include "timemaster.h"

namespace Ui {
class Valitse;
}

class Valitse : public QDialog
{
    Q_OBJECT

public:
    explicit Valitse(QWidget *parent = nullptr);
    ~Valitse();

    void setWebToken(const QByteArray &newWebToken);

    void setAccountNumber(const QString &newAccountNumber);

private slots:
    void on_btnOtto_clicked();

    void on_SaldoBtn_clicked();
    void on_btnTapahtumat_clicked();

    void on_btnSiirto_clicked();

    void on_btnQuit_clicked();

private:
    Ui::Valitse *ui;
    QByteArray webToken;
    QString accountNumber;

};

#endif // VALITSE_H
