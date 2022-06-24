#include <iostream>

#include "carriersystem.h"
#include "station.h"
#include "structsandenums.h"

using namespace std;

int main()
{
    CarrierSystem network(3, 3);
    NetworkMessage messages[3];
    int tick = -1;
    while(tick <= 6000)
    {
        network.startNetwork(messages);

        for(int i = 0; i < 3; i++)
        {
            cout << messages[i].isMessage << " " \
                 << messages[i].transmitingSation << " " \
                 << messages[i].recievingStation << endl;
        }
        cout << tick << endl;
        tick++;
    }

    return 0;
}
