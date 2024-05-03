#include "pindll.h"

Pindll::Pindll() {}

void Pindll::openDllDialog()
{
    objectDialog = new Dialog;
    objectDialog->exec();
    pinValue = objectDialog->getPin();

}

QString Pindll::getPinValue() const
{
    return pinValue;
}

void Pindll::setPinValue(const QString &newPinValue)
{
    pinValue = newPinValue;
}
