#include <iostream>
#include <iomanip>
#include "cache_h.h"

using namespace std;





char *msg[2] = {"Miss", "Hit"};
#define NO_OF_Iterations 100 // CHange to 1,000,000
int main()
{

    cacheConfig cfg (8, 1);

    cache cache(cfg);

    unsigned int hit = 0;
    cacheResType r;
    unsigned int addr;
    cout << "Direct Mapped Cache Simulator\n";
    for (int inst = 0; inst < NO_OF_Iterations; inst++)
    {
        addr = cache.memGen2();
        r = cache.cacheSimDM(addr, cfg);
        if (r == HIT)
            hit++;
        cout << "0x" << setfill('0') << setw(8) << hex << addr << " (" << msg[r]
                << ")\n";
    }
    cout << "Hit ratio = " << (100 * hit / NO_OF_Iterations) << endl;
} 