#ifndef TIMEMASTER_H
#define TIMEMASTER_H
#include <QTimer>
#include <QObject>
#include <QDebug>
#include "saldo.h"


class timemaster : public QObject
{
    Q_OBJECT

public:
    timemaster();
    ~timemaster();

private:
    QTimer *mastertimer;
    int remainingTime;
    static timemaster* instance;
    QList<QObject *> terminateList;

public:
    static timemaster* getInstance();
    void addObjectForTermination(QObject *object);
    void terminateObjects();

public slots:
    void timeOutSlot();
    void updateTimeSlot();
    void refreshRemainingTime();
    void refreshEndscreenTime();

};

#endif // TIMEMASTER_H
