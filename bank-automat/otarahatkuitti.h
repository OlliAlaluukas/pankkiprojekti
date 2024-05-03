#ifndef OTARAHATKUITTI_H
#define OTARAHATKUITTI_H

#include <QDialog>

namespace Ui {
class OtaRahatKuitti;
}

class OtaRahatKuitti : public QDialog
{
    Q_OBJECT

public:
    explicit OtaRahatKuitti(QWidget *parent = nullptr);
    ~OtaRahatKuitti();

private:
    Ui::OtaRahatKuitti *ui;
};

#endif // OTARAHATKUITTI_H
