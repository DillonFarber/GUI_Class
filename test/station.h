#ifndef STATION_H
#define STATION_H

#include "structsandenums.h"

class Station
{
public:
    Station();
    Station(int id, int loc);
    ~Station();
    int getStationID();
    void setStationID(int id);
    NetworkMessage startEvent(NetworkMessage *network, int tick, int numStations);
    int getLocation();
    void setLocation(int loc);

private:
    int stationID;
    int stationLoc;
    bool isSending = false;
    bool senseCarrier = false;
    bool isWating = false;
    int watingTick;
    int messageLen = 0;
    NetworkMessage buffer;
    bool getStatus();
    bool sensingCarrier(NetworkMessage *networkArray);
    void decrementMessage();
    bool canSend(int tick);
};

#endif // STATION_H
