#include "network.h"
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>



network::network()
{
    for(int i = 0; i < 3; i++)
        stations[i].stationID = i;
}

// methods

void network::checkSending(int curTick, int stationID)
{
    for(int i = 0; i < 10; i++)
    {
        if(!messages[i].isEmpty)
            if(messages[i].sendingStation == stationID)
            {
                stations[stationID].isIdle = false;
                stations[stationID].isSending = true;
            }
    }
}

void network::convertProbability()
{

}

void network::sensingDownCarrier(int curTick, int stationID)
{
    int checkTick;
    if(stations[stationID].isIdle)
    {
        for(int i = 0; i < 10; i++)
        {
            if(!messages[i].isEmpty && messages[i].sendingStation != stationID &&
                    messages[i].timeOfSending < curTick && messages[i].timeOfRecieving > curTick)
            {
                int distTraveled = curTick - messages[i].timeOfSending;
                int distFinish = messages[i].timeOfRecieving;
                int howFar;
                if(stationID != 1)
                {
                    if(messages[i].sendingStation != 1)
                        howFar = lengthOfMessage * 2;
                    else
                        howFar = lengthOfMessage;
                }
                else
                    howFar = lengthOfMessage;
                int position = howFar - distTraveled;
                if(position < this->sensingDistance)
                {
                    stations[stationID].isIdle = false;
                    stations[stationID].isPassing = true;
                }
                position = howFar - distFinish;
                if(position <= this->sensingDistance)
                {
                    stations[stationID].isIdle = false;
                    stations[stationID].isPassing = true;
                }
                else
                {
                    stations[stationID].isIdle = true;
                    stations[stationID].isPassing = false;
                }
            }

        }
    }
}

void network::sensingCarrier(int curTick, int stationsID)
{
    for(int i = 0; i < 10; i++)
    {
        if(!messages[i].isEmpty)
        {
            if(messages[i].sendingStation != stationsID && messages[i].timeOfSending < curTick)
            {
                if(messages[i].recievingStation == stationsID && messages[i].timeOfRecieving == curTick)
                {
                    stations[stationsID].isRecieving = true;
                    stations[stationsID].isIdle = false;
                }
                else if(messages[i].recievingStation != stationsID && curTick > messages[i].timeOfSending)
                {
                    if(stationsID == 1)
                    {
                        if(stations[stationsID].passingTick != curTick)
                        {
                        int passingTick = messages[i].timeOfSending + this->lengthOfMessage;
                        if(passingTick == curTick)
                        {
                            stations[stationsID].isIdle = false;
                            stations[stationsID].isPassing = true;
                            stations[stationsID].passingTick = passingTick;
                        }
                        else
                        {
                            stations[stationsID].isIdle = true;
                            stations[stationsID].passingTick = passingTick;
                        }
                        }
                    }
                }
            }
        }
    }
}

int network::getRandomNum(int mod)
{
    int random = (rand() % mod) + 1;
    return random;
}

double network::probability()
{
    double prob = (double) (rand() % 100) + 1;
    prob = prob / 100;
    return prob;
}

//slots

void network::sensingDistanceTicks(int distance)
{
    this->sensingDistance = distance;
}

void network::lengthOfCable(int len)
{
    this->distance = len;
}

void network::numberOfTicks(int ticks)
{
    this->runTime = ticks;
}

void network::messageLength(int len)
{
    this->lengthOfMessage = len;
}

void network::probabilityOfMessage(int prob)
{
    this->probOfMessage = prob % 100;
}

void network::run()
{
    int randomNum;
    int addTickTime;
    int tick = 0;
    bool messageCreated = false;
    std::ofstream fout;
    fout.open("output.csv");
    fout << "tick,source,destination,length" << std::endl;

    if(!fout.is_open())
        return;

    while(tick <= this->runTime)
    {
        for(int i = 0; i < 3; i++)
        {
            if(stations[i].isSending)
            {
                stations[i].sendingCount--;
                if(stations[i].sendingCount == 0)
                {
                    stations[i].isSending = false;
                    stations[i].isIdle = true;
                }
            }

            if(stations[i].isIdle)
            {
                double numran = probability();
                if(numran < this->probOfMessage)
                {
                    if(stations[i].isPassing && stations[i].passingTick == tick)
                    {
                        addTickTime = getRandomNum(4) + 1;
                        stations[i].isPassing = false;
                    }
                    else
                    {
                        addTickTime = 0;
                    }
                    messageCreated = false;
                    for(int j = 0; j < 10; j++)
                    {
                        if((!messages[j].isEmpty) && stations[i].stationID == messages[i].sendingStation && messages[j].timeOfSending == tick)
                        {
                            messages[j].isEmpty = true;
                            fout << tick << ",S"
                                 << messages[j].sendingStation + 1 << ",S"
                                 << messages[j].recievingStation + 1 << ","
                                 << messages[j].messagelen << std::endl;
                            std::cout << tick << ",S"
                                      << messages[j].sendingStation + 1 << ",S"
                                      << messages[j].recievingStation + 1 << ","
                                      << messages[j].messagelen << std::endl;
                            numMessages++;
                        }
                        if(!messageCreated && (messages[j].isEmpty || messages[j].timeOfSending < tick))
                        {
                            messageCreated = true;
                            messages[j].isEmpty = false;
                            messages[j].sendingStation = i;
                            do{
                                randomNum = getRandomNum(3);
                            }while(randomNum == i);
                            messages[j].recievingStation = randomNum;
                            messages[j].timeOfSending = tick + addTickTime;
                            messages[j].timeOfRecieving = tick + (distance * (abs(randomNum - i))) + addTickTime;
                            messages[j].messagelen = getRandomNum(3) + 1;
                            stations[i].isIdle = false;
                            if(messages[j].timeOfSending == tick)
                            {
                                stations[i].sendingCount = messages[j].messagelen;
                                stations[i].isSending = true;
                            }
                            else
                            {
                                stations[i].sendingCount = messages[j].messagelen + 1;
                            }
                            if(distance * (abs(randomNum - i)) > distance)
                            {
                                stations[1].isPassing = true;
                                stations[1].passingTick = tick + distance;
                            }
                            else
                            {
                                if(messages[j].timeOfSending == tick)
                                {

                                    messages[j].isEmpty = true;
                                    fout << tick << ",S"
                                         << messages[j].sendingStation + 1
                                         << ",S"
                                         << messages[j].recievingStation + 1
                                         << "," << messages[j].messagelen
                                         << std::endl;

                                    std::cout
                                        << tick << ",S"
                                        << messages[j].sendingStation + 1
                                        << ",S"
                                        << messages[j].recievingStation + 1
                                        << "," << messages[j].messagelen
                                        << std::endl;


                                    numMessages++;
                                }
                            }
                        }
                    }
                }
            }
        }

        tick++;
    }

}
