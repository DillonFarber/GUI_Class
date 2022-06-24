#ifndef STRUCTSANDENUMS_H
#define STRUCTSANDENUMS_H
#include <iostream>
#include <cstdlib>

struct  NetworkMessage
{
    bool isEmpty = true;
    bool isMessaging = false;
    int sendingStation;
    int recievingStation;
    int stationLoc;
    int timeOfSending = 0;
    int timeOfRecieving = 0;
    int timeItTakes = 0;
    int messagelen = 0;
};

#endif // STRUCTSANDENUMS_H
