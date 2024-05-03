#ifndef NOSTOMUUSUMMA_H
#define NOSTOMUUSUMMA_H

#include <QDialog>
#include "nosto.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class NostoMuuSumma;
}

class NostoMuuSumma : public QDialog
{
    Q_OBJECT

public:
    explicit NostoMuuSumma(QWidget *parent = nullptr);
    ~NostoMuuSumma();


    void setAccountNumber(const QString &newAccountNumber);

    void setWebToken(const QByteArray &newWebToken);

private slots:

    void on_takaisinBtn_clicked();

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

    void httpPost(QString RahaMaara);
    void nostoSlot (QNetworkReply *reply);



    void on_btnQuit_clicked();

private:
    Ui::NostoMuuSumma *ui;
    QByteArray webToken;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString accountNumber;
};

#endif // NOSTOMUUSUMMA_H
