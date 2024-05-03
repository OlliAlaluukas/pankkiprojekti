#include "environment.h"
#include "otarahatkuitti.h"
#include "tilitapahtumat.h"
#include "timemaster.h"
#include "ui_tilitapahtumat.h"

#include <QStandardItemModel>


tilitapahtumat::tilitapahtumat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tilitapahtumat)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
}

tilitapahtumat::~tilitapahtumat()
{
    delete ui;
}
void tilitapahtumat::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
    qDebug() << accountNumber;
}

void tilitapahtumat::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

void tilitapahtumat::sendRequest()
{
    QString site_url=Environment::getBaseUrl()+"/transaction/"+accountNumber;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    eventManager = new QNetworkAccessManager(this);
    connect(eventManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleResponseData(QNetworkReply*)));
    reply = eventManager->get(request);
}

void tilitapahtumat::handleResponseData(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    json_array = json_doc.array();
    qDebug()<<json_array.size();
    index=json_array.size();
    qDebug()<<index;
    populateList();
}

void tilitapahtumat::populateList()
{
    QStandardItemModel *table_model = new QStandardItemModel(transactionsList.size(),5);
    table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Tili"));
    table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Aika"));
    table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tapahtuma"));
    table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Summa"));
    table_model->setHeaderData(4, Qt::Horizontal, QObject::tr("Saaja/Maksaja"));
 //   table_model->setHeaderData(5, Qt::Horizontal, QObject::tr("Sivu"));



    for (int row=0; row < 5 && ((index-row)-1) >= 0  && ((index-row)-1) < json_array.size(); row++) {
        QJsonObject json_obj = json_array.at((index-row)-1).toObject();
        QStandardItem *idAccount = new QStandardItem((json_obj["idAccount"].toString()));
        table_model->setItem(row, 0, idAccount);
        QDateTime dateTime = QDateTime::fromString(json_obj["dateAndTime"].toString().chopped(5).replace(10, 1, " "), "yyyy-MM-dd hh:mm:ss");
        QStandardItem *dateAndTime = new QStandardItem(dateTime.toString("dd.MM.yyyy hh:mm:ss"));
        table_model->setItem(row, 1, dateAndTime);
        QStandardItem *transactionType = new QStandardItem((json_obj["transactionType"].toString()));
        table_model->setItem(row, 2, transactionType);
        QStandardItem *transactionAmount = new QStandardItem((json_obj["transactionAmount"].toString()));
        table_model->setItem(row, 3, transactionAmount);
        QStandardItem *participantAccount = new QStandardItem((json_obj["participantAccount"].toString()));
        table_model->setItem(row, 4, participantAccount);
    }
    int page1=(index%5==0 ? (index/5) : (index/5 + 1));
    int page2=(json_array.size()%5 == 0 ? (json_array.size()/5) : (json_array.size()/5+1));
    ui->pageLabel->setText("Sivu "+QString::number(page1)+"/"+QString::number(page2));
   // QStandardItem *page = new QStandardItem(QString::number(page1)+"/"+QString::number(page2));
   // table_model->setItem(0, 5, page);
    ui->tableTransactions->setModel(table_model);
   // ui->tableTransactions->resizeColumnsToContents();
    ui->tableTransactions->setColumnWidth(0,175);
    ui->tableTransactions->setColumnWidth(1,175);
    ui->tableTransactions->setColumnWidth(2,100);
    ui->tableTransactions->setColumnWidth(3,100);
    ui->tableTransactions->setColumnWidth(4,175);

  }

void tilitapahtumat::on_btnClose_clicked()
{
   this->close();
   timemaster *objectTimemaster = timemaster::getInstance();
   objectTimemaster->refreshRemainingTime();
}

void tilitapahtumat::on_btnGoBack_clicked()
{
   timemaster *objectTimemaster = timemaster::getInstance();
   objectTimemaster->refreshRemainingTime();
 //  qDebug()<<index;
   if (index>5) {
   index=index-5;
   populateList();
 //  qDebug()<<index;
   }
}

void tilitapahtumat::on_btnGoForward_clicked()
{
   timemaster *objectTimemaster = timemaster::getInstance();
   objectTimemaster->refreshRemainingTime();
 //  qDebug()<<index;
   if (index<=(json_array.size()-5)) {
   index=index+5;
   populateList();
 //  qDebug()<<index;
   }
}

void tilitapahtumat::on_btnQuit_clicked()
{
   OtaRahatKuitti *objectOtaRahatKuitti = new OtaRahatKuitti;
   timemaster *objectTimemaster = timemaster::getInstance();
   objectTimemaster->refreshEndscreenTime();   // kelloon 10 sekuntia 30:n sijaan
   //objectOtaRahatKuitti->setAccountNumber(accountNumber);
   objectOtaRahatKuitti -> open();
}

