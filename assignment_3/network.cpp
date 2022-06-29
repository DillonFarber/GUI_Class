#include "network.h"
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include <filesystem>
#include <string>



network::network()
{
    for(int i = 0; i < 3; i++)
        stations[i].stationID = i;
}

// methods

void network::checkSending(int curTick, int stationID)
{
    if(stations[stationID].isSending && stations->sendingTick <= curTick)
    {
        if(stations[stationID].sendingCount != 0)
        {
            stations[stationID].sendingCount--;
        }
        else
        {
            stations[stationID].isIdle = true;
            stations[stationID].isSending = false;
            stations[stationID].sendingCount = -1;
        }
    }
}

void network::convertProbability()
{
    this->probOfMessage = this->probOfMessage / 100.00;
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
                if(position < this->sensingTick)
                {
                    stations[stationID].isIdle = false;
                    stations[stationID].isPassing = true;
                }
                position = howFar - distFinish;
                if(position <= this->sensingTick)
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

void network::sensingCarrier(int curTick, int stationID)
{
    for(int i = 0; i < 10; i++)
    {
        if(!messages[i].isEmpty)
        {
            if(messages[i].sendingStation != stationID && messages[i].timeOfSending < curTick)
            {
                if(messages[i].recievingStation == stationID && messages[i].timeOfRecieving == curTick)
                {
                    stations[stationID].isRecieving = true;
                    stations[stationID].isIdle = false;
                    stations[stationID].recievingCount = messages[i].messagelen - 1;
                }
                else if(messages[i].recievingStation == stationID && stations[stationID].recievingCount > 0)
                {
                    stations[stationID].recievingCount--;
                    if(stations[stationID].recievingCount == 0)
                    {
                        stations[stationID].isRecieving = false;
                        stations[stationID].recievingCount =  -1;
                    }
                }
                else if(curTick > messages[i].timeOfSending)
                {
                    if(stationID == 1 && stationID != messages[i].recievingStation)
                    {
                        if(stations[stationID].passingTick == -1)
                        {
                            int passingTick = messages[i].timeOfSending + this->lengthOfMessage;
                            if(passingTick == curTick)
                            {
                                stations[stationID].isIdle = false;
                                stations[stationID].isPassing = true;
                                stations[stationID].passingTick = passingTick;
                            }
                            else
                            {
                                stations[stationID].isIdle = true;
                                stations[stationID].passingTick = passingTick;
                            }
                        }
                        else if(stations[stationID].passingTick < curTick)
                        {
                            stations[stationID].isIdle = true;
                            stations[stationID].isPassing = false;
                            stations[stationID].passingTick = -1;
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

void network::sensingDistanceTicks(int ticks)
{
    this->sensingTick = ticks;
    checkAllSet();
}

void network::lengthOfCable(int len)
{
    this->distance = len;
    checkAllSet();
}

void network::numberOfTicks(int ticks)
{
    this->runTime = ticks;
    checkAllSet();
}

void network::messageLength(int len)
{
    this->lengthOfMessage = len;
    checkAllSet();
}

void network::probabilityOfMessage(int prob)
{
    this->probOfMessage = (double) prob / 100.00;
    checkAllSet();
}

void network::run()
{
    int randomNum;
    int addTickTime;
    int tick = 0;
    bool messageCreated = false;
    std::string file;
    std::filesystem::path p = std::filesystem::current_path();
    file.append(p.string());
    file.append("\\output.csv");

    std::ofstream fout;
    fout.open(file);
    fout << "tick,source,destination,length" << std::endl;

    if(!fout.is_open())
        return;

    while(tick < this->runTime)
    {
        for(int i = 0; i < 3; i++)
        {
            checkSending(tick, i);
            sensingCarrier(tick, i);
            if(stations[i].isIdle)
            {
                double numran = probability();
                if(numran < this->probOfMessage)
                {
                    if((stations[i].isPassing && stations[i].passingTick == tick) || stations[i].isRecieving)
                    {
                        addTickTime = getRandomNum(this->sensingTick);
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
                            messages[j].timeOfRecieving = tick + (this->distance * (abs(randomNum - i))) + addTickTime;
                            messages[j].messagelen = getRandomNum(this->lengthOfMessage);
                            stations[i].isIdle = false;
                            if(messages[j].timeOfSending == tick)
                            {
                                stations[i].sendingCount = messages[j].messagelen - 1;
                                stations[i].isSending = true;
                            }
                            else
                                stations[i].sendingCount = messages[j].messagelen;
                            if(this->distance * (abs(randomNum - i)) > this->distance)
                                stations[1].passingTick = tick + this->distance;
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
    fout.close();
}

//Signals

void network::checkAllSet()
{
    if(distance != NULL && sensingTick != NULL && runTime != NULL
            && lengthOfMessage != NULL && probOfMessage != NULL)
        emit allSet(true);
    else
        emit allSet(false);
}
