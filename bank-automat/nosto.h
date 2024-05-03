#ifndef NOSTO_H
#define NOSTO_H

#include <QDialog>

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include "htiedot.h"



namespace Ui {
class Nosto;
}

class Nosto : public QDialog
{
    Q_OBJECT

public:
    explicit Nosto(QWidget *parent = nullptr);
    ~Nosto();

    void setWebToken(const QByteArray &newWebToken);

    QByteArray getWebToken() const;

    void setAccountNumber(const QString &newAccountNumber);

public slots:

    void openHtiedot();

private slots:

    void on_btn20_clicked();
    void on_btn40_clicked();
    void on_btn60_clicked();
    void on_btn90_clicked();
    void on_btn140_clicked();
    void on_btn240_clicked();
    void on_btnReturn_clicked();
    void on_btnOtherSum_clicked();


    void httpPost(double RahaMaara);
    void nostoSlot (QNetworkReply *reply);


    void on_btnQuit_clicked();

private:
    Ui::Nosto *ui;
    QByteArray webToken;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString accountNumber;

signals:

};

#endif // NOSTO_H
