#include "kuitti.h"
#include "timemaster.h"
#include "ui_kuitti.h"
#include "environment.h"

#include <QStandardItemModel>


Kuitti::Kuitti(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Kuitti)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
}

Kuitti::~Kuitti()
{
    delete ui;
}

void Kuitti::getKuitti()
{


    QString site_url=Environment::getBaseUrl()+"/transaction/"+accountNumber;
    QNetworkRequest request((site_url));
    //WEBTOKEN ALKU
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("Authorization"),(webToken));
    //WEBTOKEN LOPPU
    eventManager = new QNetworkAccessManager(this);
    connect(eventManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(populateList(QNetworkReply*)));
    reply = eventManager->get(request);
    qDebug() << "get kuitti webToken:" << webToken;

}

void Kuitti::setWebToken(const QByteArray &newWebToken)
{
    webToken = newWebToken;
    qDebug()<<webToken;
}

void Kuitti::setAccountNumber(const QString &newAccountNumber)
{
    accountNumber = newAccountNumber;
    qDebug() << accountNumber;
}


void Kuitti::populateList(QNetworkReply *reply)
{
        QByteArray jsonData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isNull() || !doc.isArray()) {

            return;
        }

        QJsonArray json_array = doc.array();

        int rowCount = json_array.size() > 0 ? 1 : 0;

        QStandardItemModel *table_model = new QStandardItemModel(rowCount, 5);


        table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Tili"));
        table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Aika"));
        table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tapahtuma"));
        table_model->setHeaderData(3, Qt::Horizontal, QObject::tr("Summa"));
        table_model->setHeaderData(4, Qt::Horizontal, QObject::tr("Saaja"));
        if (rowCount > 0) {
            QJsonObject latestTransaction = json_array.last().toObject();

            table_model->setItem(0, 0, new QStandardItem(latestTransaction["idAccount"].toString()));
            QDateTime dateTime = QDateTime::fromString(latestTransaction["dateAndTime"].toString().chopped(5).replace(10, 1, " "), "yyyy-MM-dd hh:mm:ss");
            table_model->setItem(0, 1, new QStandardItem(dateTime.toString("dd.MM.yyyy hh:mm:ss")));
            table_model->setItem(0, 2, new QStandardItem(latestTransaction["transactionType"].toString()));
            table_model->setItem(0, 3, new QStandardItem(latestTransaction["transactionAmount"].toString()));
            table_model->setItem(0, 4, new QStandardItem(latestTransaction["participantAccount"].toString()));
        }

        ui->tableView->setModel(table_model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->setColumnWidth(0,175);
        ui->tableView->setColumnWidth(1,175);
        ui->tableView->setColumnWidth(2,100);
        ui->tableView->setColumnWidth(3,100);
        ui->tableView->setColumnWidth(4,175);
}



