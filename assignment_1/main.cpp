#include <iostream>
#include <cmath>
#include <random>
#include <fstream>

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
    int passTick = -1;
};

using namespace std;


int getRandomNum(int mod);
float probability();


int main()
{
    NetworkMessage messages[10];
    Station stations[3];

    for(int i = 0; i < 3; i++)
        stations[i].stationID = i;

    int distance = 3;
    int randomNum;
    int tick = 0;
    int addTickTime;
    int numMessages = 0;
    // srand(time(0));
    ofstream fout;
    fout.open("output.csv");
    fout << "tick,source,destination,length" << endl;
    bool messageCreated = false;
    if(!fout.is_open())
        return -1;
    while(tick <= 6000)
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
                float numran = probability();
                if(numran < .100001)
                {
                    if(stations[i].isPassing && stations[i].passTick == tick)
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
                            fout << tick << ",S" << messages[j].sendingStation + 1 << ",S" << messages[j].recievingStation + 1 \
                                << "," << messages[j].messagelen << endl;
                            std::cout << tick << ",S" << messages[j].sendingStation + 1 << ",S" << messages[j].recievingStation + 1 \
                                << "," << messages[j].messagelen << endl;
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
                                stations[1].passTick = tick + distance;
                            }
                            else
                            {
                                if(messages[j].timeOfSending == tick)
                                {

                                    messages[j].isEmpty = true;
                                    fout << tick << ",S" << messages[j].sendingStation + 1 << ",S" << messages[j].recievingStation + 1 \
                                         << "," << messages[j].messagelen << endl;

                                    std::cout << tick << ",S" << messages[j].sendingStation + 1 << ",S" << messages[j].recievingStation + 1 \
                                         << "," << messages[j].messagelen << endl;
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
    fout << "number,of,messages," << numMessages << endl;
    fout.close();
    return 0;
}

int getRandomNum(int mod)
{
    int num;
    num = rand() % mod;
    return num;
}
float probability()
{
    float num = (float) rand() / RAND_MAX;
    return num;
}
