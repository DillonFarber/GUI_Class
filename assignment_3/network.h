#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include "networkStructures.h"

class network: public QObject
{
    Q_OBJECT

private:
    NetworkMessage messages[10];
    Station stations[3];
    int distance;
    int sensingTick;
    int runTime;
    int numMessages = 0;
    int lengthOfMessage;
    double probOfMessage;
    int getRandomNum(int);
    double probability();
    void checkSending(int, int);
    void convertProbability();
    void sensingDownCarrier(int, int);
    void sensingCarrier(int, int);

signals:

public slots:
    void sensingDistanceTicks(int);
    void lengthOfCable(int);
    void numberOfTicks(int);
    void messageLength(int);
    void probabilityOfMessage(int);
    void run();

public:
    network();
};

#endif // NETWORK_H
