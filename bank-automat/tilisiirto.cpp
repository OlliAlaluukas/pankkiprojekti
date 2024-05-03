#include "tilisiirto.h"
#include "otarahatkuitti.h"
#include "timemaster.h"
#include "ui_tilisiirto.h"
#include <QMessageBox>
#include <environment.h>
#include "htiedot.h"

tilisiirto::tilisiirto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tilisiirto)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
}

tilisiirto::~tilisiirto()
{
    delete ui;
}

void tilisiirto::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void tilisiirto::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
}

void tilisiirto::on_btn1_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn1->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn2_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn2->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn3_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn3->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn4_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn4->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn5_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn5->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn6_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn6->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn7_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn7->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn8_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn8->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn9_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn9->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btn0_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btn0->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btnReset_clicked()
{
    ui->lineEdit->setText("FI");
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}


void tilisiirto::on_btnErase_clicked()
{
    QString currentText = ui->lineEdit->text();
    if(currentText.length() >2){
    ui->lineEdit->QLineEdit::backspace();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    }
}


void tilisiirto::on_btnOK_clicked()
{
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    QString currentText = ui->lineEdit->text();
    QString summa;
    //qDebug() << ui->lineEdit->text().mid(0, 2);
    if(ui->lineEdit->text().mid(0, 2) == "FI" && currentText.length()==18){
        participantAccount = currentText;
        qDebug() << "tämä on accountti " << participantAccount;
    }
    else{
        summa = currentText;
        qDebug() << "tämä on summa " << summa;
        qDebug() << "tämä lähtee postiin " << participantAccount;
        tilisiirtoPost(participantAccount, summa);
    }


    ui->label->setText("Syötä siirrettävä summa");
    ui->lineEdit->clear();
  //  }

}


void tilisiirto::on_btnDot_clicked()
{
    QString currentText = ui->lineEdit->text();
    ui->lineEdit->setText(currentText+ui->btnDot->text());
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}

void tilisiirto::tilisiirtoSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QMessageBox msgBox;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObj = jsonDoc.object();
    int affectedRows = jsonObj.value("affectedRows").toInt();

    if (affectedRows > 0) {
        qDebug() << "Tilisiirto onnistui!";
        msgBox.setText("Tilisiirto onnistui!");
        QTimer timer;
        timer.setSingleShot(true);
        connect(&timer, &QTimer::timeout, &msgBox, &QMessageBox::close);
        timer.start(2000);
        msgBox.exec();
        Htiedot * objectHtiedot = new Htiedot;
        objectHtiedot -> setWebToken(webToken);
        objectHtiedot->setAccountNumber(accountNumber);
        objectHtiedot->show();
        this->close();
    } else {
        qDebug() << "Tilisiirron suorittaminen epäonnistui.";
        msgBox.setText("Tilisiirron suorittaminen epäonnistui");
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

void tilisiirto::tilisiirtoPost(QString secondAccount, QString Sum)
{

    QJsonObject jsonObj;
    jsonObj.insert("firstid", accountNumber);
    jsonObj.insert("secondid", secondAccount);
    jsonObj.insert("amount", Sum);
    qDebug() << secondAccount;

    QString site_url=Environment::getBaseUrl()+"/procedures/siirto";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    request.setRawHeader(QByteArray("Authorization"),(webToken));

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tilisiirtoSlot(QNetworkReply*)));
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}


void tilisiirto::on_btnBack_clicked()
{
    this->close();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
}




void tilisiirto::on_btnQuit_clicked()
{
        OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
        timemaster *objectTimemaster = timemaster::getInstance();
        objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
        //objectOtaRahatKuitti->setAccountNumber(accountNumber);
        objectOtaRahatKuitti -> open();
}

