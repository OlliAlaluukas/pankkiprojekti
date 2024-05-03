#include "timemaster.h"

timemaster* timemaster::instance = nullptr;

timemaster* timemaster::getInstance()
{
    if (instance == nullptr)
    {
        instance = new timemaster();
    }
    return instance;
}

timemaster::timemaster()
{
    qDebug()<<"Timemasterin kello luotu";
    remainingTime = 30;
    mastertimer = new QTimer(this);
    connect(mastertimer, &QTimer::timeout, this, &timemaster::updateTimeSlot);
    mastertimer->start(1000);
}

timemaster::~timemaster()
{
}

void timemaster::updateTimeSlot(){
    {
        if (remainingTime > 0) {
            qDebug() << "Remaining time:" << remainingTime << "seconds";
            remainingTime--;
        } else {
            timeOutSlot();
        }
    }
}

void timemaster::refreshRemainingTime()
{
    remainingTime=30;
    mastertimer->start(1000);
}

void timemaster::refreshEndscreenTime()
{
    remainingTime=10;
}

void timemaster::addObjectForTermination(QObject *object)
{
    if (object) {
        qDebug()<< "Lisätään "+object->objectName()+" tuhottavaksi";
        terminateList.append(object);
    }
}

void timemaster::terminateObjects(){
    qDebug()<<"Terminoidaan:";
    for (QObject *obj : std::as_const(terminateList)) {
        if (obj) {
               qDebug() << obj;
               delete obj;
               obj = nullptr;

        }
        }
       terminateList.clear();
    }



void timemaster::timeOutSlot()
{
    qDebug() << "Timeout";
    mastertimer->stop();
    timemaster::terminateObjects();
}
