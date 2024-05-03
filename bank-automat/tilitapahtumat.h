#ifndef TILITAPAHTUMAT_H
#define TILITAPAHTUMAT_H

#include <QDialog>

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

namespace Ui {
class tilitapahtumat;
}

class tilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit tilitapahtumat(QWidget *parent = nullptr);
    ~tilitapahtumat();

    void setWebToken(const QByteArray &newWebToken);
    void setAccountNumber(const QString &newAccountNumber);
    void sendRequest();

private slots:

    void handleResponseData(QNetworkReply *reply);
    void on_btnClose_clicked();
    void on_btnGoBack_clicked();
    void on_btnGoForward_clicked();
    void on_btnQuit_clicked();

private:
    Ui::tilitapahtumat *ui;
    QByteArray webToken;
    QString accountNumber;
    QNetworkAccessManager *eventManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QList<QString> transactionsList;
    QJsonArray json_array;
    void populateList();
    int index;

};

#endif // TILITAPAHTUMAT_H
