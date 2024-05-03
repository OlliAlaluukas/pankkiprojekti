#include "otarahatkuitti.h"
#include "timemaster.h"
#include "ui_otarahatkuitti.h"

OtaRahatKuitti::OtaRahatKuitti(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OtaRahatKuitti)
{
    ui->setupUi(this);
    timemaster *objectTimemaster = timemaster::getInstance();
    objectTimemaster->addObjectForTermination(this);
}

OtaRahatKuitti::~OtaRahatKuitti()
{
    delete ui;
}
