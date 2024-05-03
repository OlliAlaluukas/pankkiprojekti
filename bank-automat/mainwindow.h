#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <SerialReaderdll.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getCardNumber() const;

    void setCardNumber(const QString &newCardNumber);

private:
    Ui::MainWindow *ui;
    SerialReaderdll *objectSerialReader;
    QNetworkAccessManager *getManager;
    QNetworkReply *reply;
    QByteArray response_data;
    QNetworkAccessManager *loginManager;
    QByteArray webToken;
    void etsiTili(QByteArray token, QString cardNumber);
        QString idCard;
    QNetworkAccessManager *accountManager;
    QNetworkAccessManager *pinCheckManager;
    QNetworkAccessManager *setInvalidManager;
    int pinCount=0;
    void cardSetInvalid(QString cardNumber);

private slots:
    void cardCheckValid(QString cardNumber);
    void showCardNumberSlot(QString);
 //   void on_btnTest_clicked();
    void loginSlot(QNetworkReply *reply);
    void accountSlot(QNetworkReply *reply);
    void cardCheckValidSlot(QNetworkReply *reply, const QString &cardNumber);
    void cardSetInvalidSlot(QNetworkReply *reply);
};
#endif // MAINWINDOW_H
