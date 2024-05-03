#include "valitse.h"
#include "otarahatkuitti.h"
#include "tilitapahtumat.h"
#include "ui_valitse.h"
#include "nosto.h"
#include "tilisiirto.h"

Valitse::Valitse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Valitse)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
    objectTimemaster->refreshRemainingTime();
}

Valitse::~Valitse()
{
    delete ui;
}


void Valitse::on_btnOtto_clicked()
{
    Nosto *objectNosto = new Nosto;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    objectNosto -> setWebToken(webToken);
    objectNosto->setAccountNumber(accountNumber);
    objectNosto -> open();
    }

void Valitse::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
    qDebug() << accountNumber;
}

void Valitse::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    //qDebug()<<webToken;
}

void Valitse::on_SaldoBtn_clicked()
{
    Saldo *objectSaldo = new Saldo;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    qDebug() << "saldoBtn";
    qDebug() << webToken;
    objectSaldo -> setWebToken(webToken);
    objectSaldo -> setAccountNumber(accountNumber);
    objectSaldo -> getSaldo();
    objectSaldo -> open();
}
void Valitse::on_btnTapahtumat_clicked()
{
    tilitapahtumat *objectTilitapahtumat = new tilitapahtumat;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    objectTilitapahtumat->setWebToken(webToken);
    objectTilitapahtumat->setAccountNumber(accountNumber);
    objectTilitapahtumat->sendRequest();
    objectTilitapahtumat->open();
}

void Valitse::on_btnSiirto_clicked()
{
    tilisiirto *objectTilisiirto = new tilisiirto;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshRemainingTime();
    objectTilisiirto->setWebToken(webToken);
    objectTilisiirto->setAccountNumber(accountNumber);
    objectTilisiirto -> open();
}


void Valitse::on_btnQuit_clicked()
{
    OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
    //objectOtaRahatKuitti->setAccountNumber(accountNumber);
    objectOtaRahatKuitti -> open();
}

