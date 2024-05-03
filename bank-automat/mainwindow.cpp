#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "valitse.h"
#include "valitsetili.h"
#include <QMessageBox>
#include <environment.h>
#include <pindll.h>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    objectSerialReader = new SerialReaderdll;
    connect(objectSerialReader,SIGNAL(serialRead(QString)),
        this,SLOT(cardCheckValid(QString)));
    //testaus ilman serialReaderia
    //cardCheckValid("0500CB1EDE");
    //connect(objectSerialReader,SIGNAL(serialRead(QString)),
    //   this,SLOT(pinCheckSlot(QString)));

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::etsiTili(QByteArray token, QString cardNumber)
{

    QString site_url=Environment::getBaseUrl()+"/accountNumber/"+cardNumber;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"),(token));
    accountManager = new QNetworkAccessManager(this);
    connect(accountManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(accountSlot(QNetworkReply*)));
    reply = accountManager->get(request);

}

void MainWindow::cardCheckValid(QString cardNumber)
{
    pinCount=0;
    qDebug() << "cardCheckValid";
    QString site_url=Environment::getBaseUrl()+"/invalidcard/"+cardNumber;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    pinCheckManager = new QNetworkAccessManager(this);
    connect(pinCheckManager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
        cardCheckValidSlot(reply, cardNumber);});       // välitetään sekä reply että cardNumber
    reply = pinCheckManager->get(request);

}

void MainWindow::cardCheckValidSlot(QNetworkReply *reply, const QString &cardNumber)
{
    QMessageBox msgBox;
    qDebug() << "cardCheckValidSlot";
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString pinValid = QString::number(json_obj["cardValid"].toInt());
    if(response_data=="-4078" || response_data.length()==0){
        msgBox.setText("Virhe tietoyhteydessä. Yritä myöhemmin uudelleen.");
            msgBox.exec();
    }
    else {
    if ( pinValid == "0"){
        qDebug() << "ei validi";
        msgBox.setText("Kortti on lukittu. Ole hyvä ja ota yhteyttä asiakaspalveluun.");
        QTimer timer;
        timer.setSingleShot(true);
        connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
        timer.start(3000);
        msgBox.exec();
        }
    else{
    qDebug() << "validi";
    qDebug() << response_data;
    qDebug() << pinValid;
    qDebug() << cardNumber;
    reply->deleteLater();
    pinCheckManager->deleteLater();
    showCardNumberSlot(cardNumber);
        }
    }
}

void MainWindow::showCardNumberSlot(QString value)
{
    qDebug() << value;
    qDebug() << "showCardNumberSlot";
    Pindll *objectPindll = new Pindll;
    objectPindll->openDllDialog();
    QString pin = objectPindll->getPinValue();
    qDebug() << pin;
    if (pin=="x") return;
    idCard = value;
    QString idPin = pin;
    QJsonObject jsonObj;
    jsonObj.insert("idCard",idCard);
    jsonObj.insert("cardPin",idPin);

    QString site_url=Environment::getBaseUrl()+"/login";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    loginManager = new QNetworkAccessManager(this);
    connect(loginManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(loginSlot(QNetworkReply*)));
    reply = loginManager->post(request, QJsonDocument(jsonObj).toJson());
}
/*
void MainWindow::on_btnTest_clicked()
{
    //Pindll *objectPindll = new Pindll;
    //objectPindll->openDllDialog();
    cardCheckValid("0500CB1EDE");
}
*/
void MainWindow::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QMessageBox msgBox;
    if(response_data=="-4078" || response_data.length()==0){
        msgBox.setText("Virhe tietoyhteydessä. Yritä myöhemmin uudelleen.");
            msgBox.exec();
    }
    else{
        if(response_data!="false"){
            //kirjautuminen onnistui
            msgBox.setText("Kirjautuminen onnistui");
            QTimer timer;
            timer.setSingleShot(true);
            connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
            timer.start(2000);
            msgBox.exec();

            webToken = "Bearer "+response_data;
            qDebug() << webToken;
          //  Valitse *objectValitse = new Valitse;     //tämä vei suoraan valitse-näkymään etsitilin ohi
          //  objectValitse -> setWebToken(webToken);
          //  objectValitse -> open();
            etsiTili(webToken, idCard);
        }

        else{
            msgBox.setText("Tunnus/salasana ei täsmää");
            QTimer timer;
            timer.setSingleShot(true);
            connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
            timer.start(2000);
            msgBox.exec();
            pinCount++;
            qDebug() << pinCount;
            if (pinCount >= 3) {
                cardSetInvalid(idCard);
            }
            else {
                showCardNumberSlot(idCard);
            }
        }

  //  reply->deleteLater();
  //  loginManager->deleteLater();
}
}

void MainWindow::accountSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug() << response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    reply->deleteLater();
    accountManager->deleteLater();
    qDebug() << json_array.size();
    if (json_array.size() == 2)
    {
        qDebug() << "avataan valitsetili";
        QString creditLimit1 = json_array.at(0)["creditLimit"].toString();
        QString debitNumber;
        QString creditNumber;
        if (creditLimit1 == "0.00"){
            debitNumber = json_array.at(0)["idAccount"].toString();
            creditNumber = json_array.at(1)["idAccount"].toString();
        }
        else {
            debitNumber = json_array.at(1)["idAccount"].toString();
            creditNumber = json_array.at(0)["idAccount"].toString();
        }
        valitseTili *objectValitseTili = new valitseTili;
        objectValitseTili->setDebit(debitNumber);
        objectValitseTili->setCredit(creditNumber);
        objectValitseTili->setWebToken(webToken);
        objectValitseTili->open();
        //qDebug() << debitNumber;


    }
    else{
        qDebug() << "mennään suoraan valitse";
        QString accountNumber = json_array.at(0)["idAccount"].toString();
        Valitse *objectValitse = new Valitse;
        objectValitse->setWebToken(webToken);
        objectValitse->setAccountNumber(accountNumber);
        objectValitse->open();
    }
}

void MainWindow::cardSetInvalid(QString cardNumber)
{
    qDebug() << "cardSetInvalid";
    QJsonObject jsonObj;
    jsonObj.insert("cardValid", 0);
    QString site_url=Environment::getBaseUrl()+"/invalidcard/"+cardNumber;
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    setInvalidManager = new QNetworkAccessManager(this);
    connect(setInvalidManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cardSetInvalidSlot(QNetworkReply*)));
    reply = setInvalidManager->put(request, QJsonDocument(jsonObj).toJson());
}


void MainWindow::cardSetInvalidSlot(QNetworkReply *reply)
{
    qDebug() << "cardSetInvalidSlot";
    response_data=reply->readAll();
    qDebug() << response_data;
    reply->deleteLater();
    setInvalidManager->deleteLater();
    cardCheckValid(idCard);
}
