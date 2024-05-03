#include "valitsetili.h"
#include "otarahatkuitti.h"
#include "ui_valitsetili.h"
#include "valitse.h"

valitseTili::valitseTili(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::valitseTili)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
    objectTimemaster->refreshRemainingTime();   // tänne ei mennä pääohjelman napista joten siksi tässä refresh
}

valitseTili::~valitseTili()
{
    delete ui;
}

void valitseTili::setCredit(const QString &newCredit)
{
    credit = newCredit;
}

void valitseTili::setDebit(const QString &newDebit)
{
    debit = newDebit;
}


void valitseTili::on_btnDebit_clicked()
{
  //  qDebug()<<debit;
    Valitse *objectValitse = new Valitse;
    objectValitse->setWebToken(webToken);
    objectValitse->setAccountNumber(debit);
    objectValitse->open();
    this -> close();
}


void valitseTili::on_btnCredit_clicked()
{
  //  qDebug()<<credit;
    Valitse *objectValitse = new Valitse;
    objectValitse->setWebToken(webToken);
    objectValitse->setAccountNumber(credit);
    objectValitse->open();
    this -> close();
}

void valitseTili::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    //qDebug()<<webToken;
}

void valitseTili::on_btnQuit_clicked()
{
    OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
    //objectOtaRahatKuitti->setAccountNumber(accountNumber);
    objectOtaRahatKuitti -> open();
}

