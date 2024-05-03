#ifndef SALDO_H
#define SALDO_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Saldo;
}

class Saldo : public QDialog
{
    Q_OBJECT

public:
    explicit Saldo(QWidget *parent = nullptr);
    ~Saldo();

    void setWebToken(const QByteArray &newWebToken);
    void getSaldo();

    void setAccountNumber(const QString &newAccountNumber);

private slots:
    void on_Lopeta_clicked();
private slots:
    void saldoSlot (QNetworkReply *reply);

    void on_btnQuit_clicked();

private:
    Ui::Saldo *ui;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QByteArray webToken;
    QString accountNumber;

};

#endif // SALDO_H
