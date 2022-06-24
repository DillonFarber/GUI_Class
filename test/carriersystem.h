#ifndef CARRIERSYSTEM_H
#define CARRIERSYSTEM_H
#include "structsandenums.h"

class Station;

class CarrierSystem
{
public:
    CarrierSystem(int numStations, int distance);
    ~CarrierSystem();
    int getTick();
    void incrementTick();
    void setNumStations(int s);
    void setDistance(int dist);
    int getNumStations();
    int getDistance();
    void setNetworkArray();
    void moveMessage();
    void startNetwork(NetworkMessage array[]);
    void deleteArrays();

private:
        int tick = -1;
        int distance;
        int numStations;
        Station *stations;
        int messageBuffer;
        NetworkMessage *networkArray;
        int netArrSize;
};


#endif // CARRIERSYSTEM_H
