#ifndef NETWORKSTRUCTURES_H
#define NETWORKSTRUCTURES_H

struct  NetworkMessage
{
    bool isEmpty = true;
    int sendingStation = -1;
    int recievingStation = -1;
    int timeOfSending = -1;
    int timeOfRecieving = -1;
    int endMessage = -1;
    int messagelen = -1;
};

struct Station
{
    bool isIdle = true;
    bool isSending = false;
    bool isRecieving = false;
    bool isPassing = false;
    int stationID = -1;
    int sendingCount = -1;
    int recievingCount = -1;
    int passingTick = -1;
};

#endif // NETWORKSTRUCTURES_H
