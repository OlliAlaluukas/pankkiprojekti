#ifndef PINDLL_H
#define PINDLL_H

#include "Pindll_global.h"
#include "dialog.h"
#include <QString>
#include <QObject>
#include <QDebug>

class PINDLL_EXPORT Pindll
{

public:
    Pindll();
    void openDllDialog();
    QString getPinValue() const;
    void setPinValue(const QString &newPinValue);

private:
    Dialog *objectDialog;
    QString pinValue;
};

#endif // PINDLL_H
