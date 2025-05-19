#include <iostream>
#include <iomanip>
#include <bitset>
#include "cache_h.h"

using namespace std;

const char *msg[2] = {"Miss", "Hit"};
#define NO_OF_Iterations 10 // Change to 1,000,000

int main() {
    cacheConfig cfg(16, 1);
    cache cache(cfg);
    addr address1;

    unsigned long hit = 0;
    cacheResType r;

    cout << "Direct Mapped Cache Simulator\n";
    for (int inst = 0; inst < NO_OF_Iterations; inst++) {
        if (inst < NO_OF_Iterations / 6)
            address1.address = cache.memGen1();
        else if (inst < 2 * NO_OF_Iterations / 6)
            address1.address = cache.memGen2();
        else if (inst < 3 * NO_OF_Iterations / 6)
            address1.address = cache.memGen3();
        else if (inst < 4 * NO_OF_Iterations / 6)
            address1.address = cache.memGen4();
        else if (inst < 5 * NO_OF_Iterations / 6)
            address1.address = cache.memGen5();
        else if (inst < NO_OF_Iterations)
            address1.address = cache.memGen6();

        address1.extractFields(cfg);


        cout << dec << inst << "    " << "0b" << setfill('0') << setw(8) << bitset<16>(address1.address) << " (" << msg[r]
                << ")\n";


        r = cache.cacheSimDM(address1);
        if (r == HIT)
            hit++;

    }

    cout << "Hit ratio DM = " << (100 * (static_cast<double>(hit) / NO_OF_Iterations)) << "%" << endl << flush;

    cout << "--------------------------------" << endl;

    /*hit = 0;
    for (int inst = 0; inst < NO_OF_Iterations; inst++) {
        address1.address = cache.memGen2();
        address1.extractFields(cfg);
        r = cache.cacheSimFA(address1);
        if (r == HIT)
            hit++;
        cout << dec << inst << "    " << "0b" << setfill('0') << setw(8) << bitset<16>(address1.address) << " (" << msg[r]
                << ")\n";
    }

    cout << "Hit ratio FA = " << (100 * (static_cast<double>(hit) / NO_OF_Iterations)) << "%" << endl << flush;*/

    return 0;
}
