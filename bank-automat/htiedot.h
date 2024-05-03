#ifndef HTIEDOT_H
#define HTIEDOT_H

#include <QDialog>

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class Htiedot;
}

class Htiedot : public QDialog
{
    Q_OBJECT

public:
    explicit Htiedot(QWidget *parent = nullptr);
    ~Htiedot();

    void setWebToken(const QByteArray &newWebToken);
    void setAccountNumber(const QString &newAccountNumber);


private slots:


    void on_EiKiitosBtn_clicked();

    void on_KuittiNaytolleBtn_clicked();

private:
    Ui::Htiedot *ui;
    QByteArray webToken;
    QString accountNumber;
    QNetworkAccessManager *eventManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // HTIEDOT_H
