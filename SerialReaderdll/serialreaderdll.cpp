#include "serialreaderdll.h"
#include <QtSerialPort/QSerialPort>

SerialReaderdll::SerialReaderdll()
{
    serialPort = new QSerialPort();
    serialPort->setPortName("com3");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->open(QIODevice::ReadWrite);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(showDataSlot()));
}

void SerialReaderdll::showDataSlot()
{
    QByteArray serialData = serialPort->readAll();
    QString cardNumber = serialData.remove(0,3);
    cardNumber.chop(3);
    emit serialRead(cardNumber);
}
