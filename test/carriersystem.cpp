#include "carriersystem.h"
#include "station.h"
#include <stdio.h>
#include <stdlib.h>

CarrierSystem::CarrierSystem(int numStations, int distance)
{
    this->numStations = numStations;
    this->distance = distance;
    this->stations = new Station [numStations];
    for(int i = 0; i < numStations; i++)
    {
        this->stations[i].setStationID(i + 1);
        if(i == 0)
            this->stations[i].setLocation(i);
        else if(i > 0 && i < numStations - 1)
            this->stations[i].setLocation(((distance) * i) + i);
        else
            this->stations[i].setLocation(numStations - 1);
    }
    setNetworkArray();
}

int CarrierSystem::getTick(){return this->tick;}

void CarrierSystem::incrementTick(){this->tick += 1;}

void CarrierSystem::setNumStations(int s)
{
    this->numStations = s;
    setNetworkArray();
}

void CarrierSystem::setDistance(int d)
{
    this->distance = d;
    setNetworkArray();
}

int CarrierSystem::getNumStations(){return this->numStations;}

int CarrierSystem::getDistance(){return this->distance;}

void CarrierSystem::setNetworkArray()
{
    this->netArrSize = 10;
    this->networkArray = new NetworkMessage[this->netArrSize];
}

void CarrierSystem::startNetwork(NetworkMessage array[])
{
    this->incrementTick();
    for(int i = 0; i < 3; i++)
    {
        array[i] = this->stations[i].startEvent(this->networkArray, this->tick, this->numStations);
    }
}

void CarrierSystem::deleteArrays()
{
    delete this->networkArray;
    delete this->stations;
}

CarrierSystem::~CarrierSystem()
{
    delete this->stations;
    delete this->networkArray;
}
