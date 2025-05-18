#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <cmath>
#include <cstdint>
#include <vector>
using namespace std;

#define DBG 1
#define DRAM_SIZE (64 * 1024 * 1024)
#define CACHE_SIZE (64 * 1024)


enum cacheResType
{
    MISS = 0,
    HIT = 1
};


struct cacheConfig
    {                          // to generalize the code and edit these values depending on each testcase
        unsigned int lineSize; // in bytes
        unsigned int numWays;  // 1 = DM, N = N-way associative
        unsigned int numSets;

        cacheConfig(unsigned int lsize, unsigned int nways)
        {
            lineSize = lsize;
            numWays = nways;
            numSets = (CACHE_SIZE / lineSize) / numWays;
        }
    };

// Cache class for Direct-Mapped cache simulation
class cache
{
private:

    

    
    struct Line
    {
        bool valid;
        uint32_t tag;
        uint32_t data;
    };
    
    vector<vector<Line>> cacheLines; // a set of lines (blocks) depending on N


    struct addr{
        uint32_t numLines; // Number of cache blocks
        uint32_t offsetBits;
        uint32_t indexBits;
        uint32_t tagBits;
    };
    

public:
    static constexpr uint32_t ADDRESS_BITS = 26;      // 64MB address space

    // Constructor
    cache(cacheConfig cache);

    // Access function returns HIT or MISS
    cacheResType access(uint32_t address);

    unsigned int rand_();
    unsigned int memGen1();
    unsigned int memGen2();
    unsigned int memGen3();
    unsigned int memGen4();
    unsigned int memGen5();
    unsigned int memGen6();

    cacheResType cacheSimDM(unsigned int addr, const cacheConfig &cfg);
    cacheResType cacheSimFA(unsigned int addr);



};

#endif // CACHE_H
