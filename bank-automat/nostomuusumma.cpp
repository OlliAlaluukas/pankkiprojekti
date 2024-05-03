#include "nostomuusumma.h"
#include "ui_nostomuusumma.h"
#include "nosto.h"
#include "htiedot.h"
#include "timemaster.h"
#include "environment.h"
#include <QMessageBox>
#include "otarahatkuitti.h"


NostoMuuSumma::NostoMuuSumma(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NostoMuuSumma)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
}

NostoMuuSumma::~NostoMuuSumma()
{
    delete ui;
}


void NostoMuuSumma::on_btn1_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn1->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn2_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn2->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn3_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn3->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn4_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn4->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn5_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn5->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn6_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn6->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn7_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn7->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn8_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn8->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn9_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn9->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btn0_clicked()
{
    QString currentText = ui->lineEdit->text();
    if (currentText.length() < 3){
        ui->lineEdit->setText(currentText+ui->btn0->text());
    }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btnReset_clicked()
{
    ui->lineEdit->clear();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void NostoMuuSumma::on_btnErase_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->QLineEdit::backspace();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}

void NostoMuuSumma::on_takaisinBtn_clicked()
{
    this -> close();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}

void NostoMuuSumma::on_btnOK_clicked()
{
    QMessageBox msgBox;
    QString currentText = ui->lineEdit->text();
    int currentNumber =currentText.toInt();
    if (currentNumber%5==0 && currentNumber < 401 && currentNumber!=0){
    httpPost(currentText);
    this -> close();
    }else{
    msgBox.setText("Virhe: Summan voi nostaa vain seteleinä");
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
    timer.start(2000);
    msgBox.exec();
         }
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}

void NostoMuuSumma::httpPost(QString RahaMaara)
{
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

void NostoMuuSumma::nostoSlot(QNetworkReply *reply)
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
    } else {
        msgBox.setText("Noston suorittaminen epäonnistui");
        QTimer timer;
        timer.setSingleShot(true);
        connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
        timer.start(2000);
        msgBox.exec();
    }

    reply->deleteLater();
    postManager->deleteLater();
    QString currentText = ui->lineEdit->text();
    int currentNumber =currentText.toInt();
    Htiedot * objectHtiedot = new Htiedot;
    objectHtiedot -> setWebToken(webToken);
    objectHtiedot->setAccountNumber(accountNumber);
    if (currentText.length() > 0 && currentNumber%5==0 && currentNumber  <401 && affectedRows >0){
        objectHtiedot->show();
    }
}

void NostoMuuSumma::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void NostoMuuSumma::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
}

void NostoMuuSumma::on_btnQuit_clicked()
{
    OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
    //objectOtaRahatKuitti->setAccountNumber(accountNumber);
    objectOtaRahatKuitti -> open();
}

