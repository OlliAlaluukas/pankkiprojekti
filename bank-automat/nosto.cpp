#include "nosto.h"
#include "ui_nosto.h"
#include "valitse.cpp"
#include "nostomuusumma.h"
#include "environment.h"
#include <QMessageBox>

Nosto::Nosto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Nosto)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
    /*
    connect(ui->btn20, &QPushButton::clicked, this, &Nosto::openHtiedot);
    connect(ui->btn40, &QPushButton::clicked, this, &Nosto::openHtiedot);
    connect(ui->btn60, &QPushButton::clicked, this, &Nosto::openHtiedot);
    connect(ui->btn90, &QPushButton::clicked, this, &Nosto::openHtiedot);
    connect(ui->btn140, &QPushButton::clicked, this, &Nosto::openHtiedot);
    connect(ui->btn240, &QPushButton::clicked, this, &Nosto::openHtiedot);
*/
}

Nosto::~Nosto()
{
    delete ui;
}

void Nosto::openHtiedot() {
    Htiedot * objectHtiedot = new Htiedot;
    objectHtiedot -> setWebToken(webToken);
    objectHtiedot->setAccountNumber(accountNumber);
    objectHtiedot->show();
}

void Nosto::on_btn20_clicked()
{
    httpPost(20);
    //void nostoSlot (QNetworkReply *reply);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}

void Nosto::on_btn40_clicked()
{
    httpPost(40);
    //void nostoSlot (QNetworkReply *reply);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void Nosto::on_btn60_clicked()
{
    httpPost(60);
    //void nostoSlot (QNetworkReply *reply);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void Nosto::on_btn90_clicked()
{
    httpPost(90);
    //void nostoSlot (QNetworkReply *reply);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void Nosto::on_btn140_clicked()
{
    httpPost(140);
    //void nostoSlot (QNetworkReply *reply);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void Nosto::on_btn240_clicked()
{
    httpPost(240);
    //void nostoSlot (QNetworkReply *reply);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void Nosto::on_btnReturn_clicked()
{
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    this -> close();
}


void Nosto::on_btnOtherSum_clicked()
{
    NostoMuuSumma *objectNostoMuuSumma = new NostoMuuSumma;
    objectNostoMuuSumma -> setWebToken(webToken);
    objectNostoMuuSumma->setAccountNumber(accountNumber);
    objectNostoMuuSumma -> open();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}

void Nosto::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    //qDebug()<<webToken;

}
void Nosto::nostoSlot (QNetworkReply *reply)
{
    QMessageBox msgBox;

response_data=reply->readAll();
qDebug()<<response_data;

QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
QJsonObject jsonObj = jsonDoc.object();
int affectedRows = jsonObj.value("affectedRows").toInt();

if (affectedRows > 0) {
    msgBox.setText("Nosto onnistui");
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
    timer.start(2000);
    msgBox.exec();
    Nosto::openHtiedot();

} else {
    msgBox.setText("Noston suorittaminen epäonnistui");
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
    timer.start(2000);
    msgBox.exec();
    this->close();
}

reply->deleteLater();
postManager->deleteLater();

}

void Nosto::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
}

void Nosto::httpPost(double RahaMaara) {

    QJsonObject jsonObj;
    jsonObj.insert("firstid", accountNumber);
    jsonObj.insert("amount", RahaMaara);


    QString site_url=Environment::getBaseUrl()+"/procedures/nosto";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(nostoSlot(QNetworkReply*)));


    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Nosto::on_btnQuit_clicked()
{
    OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
    //objectOtaRahatKuitti->setAccountNumber(accountNumber);
    objectOtaRahatKuitti -> open();
}

