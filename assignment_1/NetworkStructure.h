#ifndef NETWORKSTRUCTURE_H
#define NETWORKSTRUCTURE_H

struct  NetworkMessage
{
    bool isEmpty = true;
    int sendingStation;
    int recievingStation;
    int timeOfSending;
    int timeOfRecieving;
    int endMessage;
    int messagelen;
};

struct Station
{
    bool isIdle = true;
    bool isSending = false;
    bool isRecieving = false;
    bool isPassing = false;
    int stationID;
    int sendingCount;
    int passTick;
};

#endif // NETWORKSTRUCTURE_H
