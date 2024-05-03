#ifndef KUITTI_H
#define KUITTI_H

#include <QDialog>

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


namespace Ui {
class Kuitti;
}

class Kuitti : public QDialog
{
    Q_OBJECT

public:
explicit Kuitti(QWidget *parent = nullptr);
~Kuitti();

void getKuitti();

void setWebToken(const QByteArray &newWebToken);

void setAccountNumber(const QString &newAccountNumber);


private slots:
void populateList(QNetworkReply *reply);



private:
Ui::Kuitti *ui;
QByteArray webToken;
QString accountNumber;
QNetworkAccessManager *eventManager;
QNetworkReply *reply;
QByteArray response_data;
QList<QString> transactionsList;
QJsonArray json_array;

};

#endif // KUITTI_H
