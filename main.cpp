#include <iostream>
#include <iomanip>
#include <bitset>
#include "cache_h.h"

using namespace std;

const char *msg[2] = {"Miss", "Hit"};
const char *msg2[4] = {"Random", "FIFO", "LRU", "LFU"};
#define NO_OF_Iterations 1000000 // Change to 1,000,000

int main() {

    //First expirement: Fix the number of sets to 4 and vary the line size. Plot the hit ratio against the line size
    cout << "First expirement: Fix the number of sets to 4 and vary the line size. Plot the hit ratio against the line size" << endl;
    cout << "Direct Mapped Cache Simulator\n";
    for (int lsize = 16; lsize <= 128; lsize*=2) {
        cacheConfig cfg(lsize, 4, Random);
        cache cache0(cfg);
        addr address1;

        unsigned long hit = 0;
        cacheResType r;



        for (int inst = 0; inst < NO_OF_Iterations; inst++) {
            if (inst < NO_OF_Iterations / 6)
                address1.address = cache0.memGen1();
            else if (inst < 2 * NO_OF_Iterations / 6)
                address1.address = cache0.memGen2();
            else if (inst < 3 * NO_OF_Iterations / 6)
                address1.address = cache0.memGen3();
            else if (inst < 4 * NO_OF_Iterations / 6)
                address1.address = cache0.memGen4();
            else if (inst < 5 * NO_OF_Iterations / 6)
                address1.address = cache0.memGen5();
            else if (inst < NO_OF_Iterations)
                address1.address = cache0.memGen6();

            address1.extractFields(cfg);

            //if (inst %10000000 == 0) cout << inst << endl;
            /*cout << dec << inst << "    " << "0b" << setfill('0') << setw(8) << bitset<16>(address1.address) << " (" << msg[r]
                    << ")\n";*/


            r = cache0.cacheSimDM(address1);
            if (r == HIT)
                hit++;

        }

        cout << "Hit ratio DM = " << (100 * (static_cast<double>(hit) / NO_OF_Iterations)) << "%" << endl << flush;

        cout << "--------------------------------" << endl;
    }


    cout << endl << "----------------------------" << endl;

    //Fix the line size to 64 bytes and vary the number of sets (ways). Plot the hit ratio against the number of ways.
    cout << "Fix the line size to 64 bytes and vary the number of sets (ways). Plot the hit ratio against the number of ways." << endl;
    cout << "N - Way Cache Simulator\n";
    for (int n = 1; n <= 16; n*=2) {
        cacheConfig cfg(64, n, Random);
        cache cache1(cfg);
        addr address1;

        unsigned long hit = 0;
        cacheResType r;



        for (int inst = 0; inst < NO_OF_Iterations; inst++) {
            if (inst < NO_OF_Iterations / 6)
                address1.address = cache1.memGen1();
            else if (inst < 2 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen2();
            else if (inst < 3 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen3();
            else if (inst < 4 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen4();
            else if (inst < 5 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen5();
            else if (inst < NO_OF_Iterations)
                address1.address = cache1.memGen6();

            address1.extractFields(cfg);

            r = cache1.cacheSimNway(address1, cfg);
            if (r == HIT)
                hit++;

        }

        cout << "Hit ratio N-Way = " << (100 * (static_cast<double>(hit) / NO_OF_Iterations)) << "%" << endl << flush;

        cout << "--------------------------------" << endl;
    }





    //Extra experiment: testing which replacement type is most efficient
    cout << "Extra experiment: testing which replacement type is most efficient." << endl;
    cout << "Testing each replacement type\n";
    for (int rpl = 1; rpl <= 4; rpl++) {
        auto p = static_cast<replacementType>(rpl);
        cacheConfig cfg(16, 1, p);
        cache cache1(cfg);
        addr address1;

        unsigned long hit = 0;
        cacheResType r;



        for (int inst = 0; inst < NO_OF_Iterations; inst++) {
            if (inst < NO_OF_Iterations / 6)
                address1.address = cache1.memGen1();
            else if (inst < 2 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen2();
            else if (inst < 3 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen3();
            else if (inst < 4 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen4();
            else if (inst < 5 * NO_OF_Iterations / 6)
                address1.address = cache1.memGen5();
            else if (inst < NO_OF_Iterations)
                address1.address = cache1.memGen6();

            address1.extractFields(cfg);

            r = cache1.cacheSimFA(address1, cfg, inst);
            if (r == HIT)
                hit++;

        }

        cout << "Hit ratio" << msg2[rpl] <<":"<< (100 * (static_cast<double>(hit) / NO_OF_Iterations)) << "%" << endl << flush;

        cout << "--------------------------------" << endl;
    }


    return 0;
}
