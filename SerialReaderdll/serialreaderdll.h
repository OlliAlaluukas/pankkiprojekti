#ifndef SERIALREADERDLL_H
#define SERIALREADERDLL_H

#include "SerialReaderdll_global.h"

#include <QtSerialPort/QSerialPort>

class SERIALREADERDLL_EXPORT SerialReaderdll : public QObject
{
    Q_OBJECT
public:
    SerialReaderdll();
private:
    QSerialPort *serialPort;
private slots:
    void showDataSlot();
signals:
    void serialRead(QString value);
};

#endif // SERIALREADERDLL_H
