#include <random>
#include <time.h>

#include "station.h"

int eventStatus();
int messageLen();

Station::Station(){}

Station::Station(int id, int loc)
{
    this->stationID = id;
    this->stationLoc = loc;
}

int Station::getStationID(){return this->stationID;}

void Station::setStationID(int id){this->stationID = id;}

// false is idle, true is in prograss of action
bool Station::getStatus()
{
    if(this->isSending)
    {
        if(this->messageLen > 0)
        {
            decrementMessage();
            return true;
        }
        else
        {
            this->isSending = false;
            return false;
        }
    }
    return false;
}

NetworkMessage Station::startEvent(NetworkMessage *network, int tick, int numStations)
{
    NetworkMessage nullmessage;
    //bool sending = canSend(tick);
    //srand(time(NULL));
    this->senseCarrier = this->sensingCarrier(network);
//    if(!(sending))
//    {
//        std::cout << "after cansend test" << std::endl;
//        return nullmessage;
//    }
//    else
//    {
//        if(this->buffer.type != "null")
//            return this->buffer;
//    }
    if(!this->getStatus())
    {
        float messaging = (float) rand() / RAND_MAX;
        if(messaging < .101)
        {
            std::cout << messaging << " if messaged then .1 or less should appear here" << std::endl;
            this->isSending = true;
            this->messageLen = (rand() % 3) + 1;

            int nextStation = (rand() % numStations) + 1;
            while(nextStation == this->stationID)
            {
                nextStation = (rand() % numStations) + 1;
            }
            if(this->senseCarrier)
            {
                this->isWating = true;
                this->buffer.isMessaging = true;
                this->buffer.sendingStation = this->stationID;
                this->buffer.recievingStation = nextStation;
                this->buffer.timeOfSending = tick + 2;
                this->buffer.messagelen = messageLen;
                return nullmessage;
            }
            else
            {
                this->buffer.isEmpty = false;
                this->buffer.sendingStation = this->stationID;
                this->buffer.recievingStation = nextStation;
                this->buffer.timeOfSending = tick;
                this->buffer.messagelen = messageLen;
                this->buffer.timeOfRecieving = tick + messageLen;
                this->buffer.timeItTakes = messageLen > 1 ? (messageLen + (messageLen - 1)) *  : mess
                return this->buffer;
            }
        }
        else
            return nullmessage;
    }
    return nullmessage;

}

int Station::getLocation(){return this->stationLoc;}

void Station::setLocation(int loc){this->stationLoc = loc;}

bool Station::sensingCarrier(NetworkMessage *network)
{
    //busy if true and not busy if false
    if(network[this->stationLoc].isEmpty)
        return false;
    else
        return true;
}

void Station::decrementMessage()
{
    this->messageLen -= 1;
}

bool Station::canSend(int tick)
{
    if(this->isWating)
    {
        if(tick == this->watingTick)
        {
            this->isWating = false;
            this->isSending = true;
            this->watingTick = 0;
            return false;
        }
        else
            return true;
    }
    else
        return false;
}

Station::~Station(){}
