#include <iostream>
#include <iomanip>
#include <bitset>
#include "cache_h.h"

using namespace std;

const char *msg[2] = {"Miss", "Hit"};
#define NO_OF_Iterations 10 // Change to 1,000,000

int main() {
    cacheConfig cfg(8, 1);
    cache cache(cfg);
    addr address1;

    unsigned long hit = 0;
    cacheResType r;

    cout << "Direct Mapped Cache Simulator\n";
    for (int inst = 0; inst < NO_OF_Iterations; inst++) {
        address1.address = cache.memGen2();
        address1.extractFields(cfg);
        r = cache.cacheSimDM(address1, cfg);
        if (r == HIT)
            hit++;
        cout << dec << inst << "    " << "0b" << setfill('0') << setw(8) << bitset<16>(address1.address) << " (" << msg[r]
                << ")\n";
    }
    cout << "Hit ratio = " << (100 * (static_cast<double>(hit) / NO_OF_Iterations)) << "%" << endl << flush;
}
