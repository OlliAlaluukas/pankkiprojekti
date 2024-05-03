#ifndef TILISIIRTO_H
#define TILISIIRTO_H

#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class tilisiirto;
}

class tilisiirto : public QDialog
{
    Q_OBJECT

public:
    explicit tilisiirto(QWidget *parent = nullptr);
    ~tilisiirto();

    void setWebToken(const QByteArray &newWebToken);

    void setAccountNumber(const QString &newAccountNumber);

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

    void on_btnDot_clicked();

    void tilisiirtoSlot (QNetworkReply *reply);

    void tilisiirtoPost(QString secondAccount, QString Sum);

    void on_btnBack_clicked();

    void on_btnQuit_clicked();

private:
    Ui::tilisiirto *ui;
    QByteArray webToken;
    QString accountNumber;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString participantAccount;
};

#endif // TILISIIRTO_H
