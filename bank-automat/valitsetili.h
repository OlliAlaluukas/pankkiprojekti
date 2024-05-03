#ifndef VALITSETILI_H
#define VALITSETILI_H

#include <QDialog>

namespace Ui {
class valitseTili;
}

class valitseTili : public QDialog
{
    Q_OBJECT

public:
    explicit valitseTili(QWidget *parent = nullptr);
    ~valitseTili();

    void setWebToken(const QByteArray &newWebToken);

    void setCredit(const QString &newCredit);

    void setDebit(const QString &newDebit);

private slots:
    void on_btnDebit_clicked();

    void on_btnCredit_clicked();

    void on_btnQuit_clicked();

private:
    Ui::valitseTili *ui;
    QString credit;
    QString debit;
    QByteArray webToken;
};

#endif // VALITSETILI_H
