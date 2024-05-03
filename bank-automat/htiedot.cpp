#include "htiedot.h"
#include "ui_htiedot.h"
#include "otarahatkuitti.h"
#include "kuitti.h"
#include "nosto.h"
#include "timemaster.h"

Htiedot::Htiedot(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Htiedot)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
}

Htiedot::~Htiedot()
{
    delete ui;
}

void Htiedot::on_EiKiitosBtn_clicked()
{
    OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
    //objectOtaRahatKuitti->setAccountNumber(accountNumber);
    objectOtaRahatKuitti -> open();
}


void Htiedot::on_KuittiNaytolleBtn_clicked()
{
    Kuitti *objectKuitti = new Kuitti();
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
    objectKuitti -> setWebToken(webToken);
    objectKuitti -> getKuitti();
    objectKuitti->setAccountNumber(accountNumber);
    objectKuitti -> open();
}

void Htiedot::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
}

void Htiedot::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
    qDebug() << accountNumber;
}

