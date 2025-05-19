#include <iostream>
#include <iomanip>
#include "cache_h.h"

using namespace std;


cache::cache(const cacheConfig &cfg) {
    cacheLines.resize(cfg.numSets);

    for (auto &set : cacheLines) {
        set.resize(cfg.numWays);
        for (auto &block : set) {
            block.valid = false;
            block.tag = 0;
            block.data = 0;
        }
    }
}



/* The following implements a random number generator */
unsigned int m_w = 0xABABAB55; /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902; /* must not be zero, nor 0x9068ffff */
unsigned int cache::rand_()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w; /* 32-bit result */
}

unsigned int cache::memGen1()
{
    static unsigned int addr = 0;
    return (addr++) % (DRAM_SIZE);
}
unsigned int cache::memGen2()
{
    static unsigned int addr = 0;
    return rand_() % (24 * 1024);
}
unsigned int cache::memGen3()
{
    return rand_() % (DRAM_SIZE);
}
unsigned int cache::memGen4()
{
    static unsigned int addr = 0;
    return (addr++) % (4 * 1024);
}
unsigned int cache::memGen5()
{
    static unsigned int addr = 0;
    return (addr++) % (1024 * 64);
}
unsigned int cache::memGen6()
{
    static unsigned int addr = 0;
    return (addr += 32) % (64 * 4 * 1024);
}


// Direct Mapped Cache Simulator
cacheResType cache::cacheSimDM(addr addr)
{
    // This function accepts the memory address for the memory transaction and
    // returns whether it caused a cache miss or a cache hit
    // The current implementation assumes there is no cache; so, every transaction is a miss 
    
    if (cacheLines[addr.index][0].tag == addr.tag && cacheLines[addr.index][0].valid == true)
        return HIT;

    cacheLines[addr.index][0].tag = addr.tag;
    cacheLines[addr.index][0].valid = true;
    return MISS;
}
// Fully Associative Cache Simulator
cacheResType cache::cacheSimFA(addr address, cacheConfig cfg) {
    // Search for a hit
    for (int i = 0; i < cfg.numSets; i++) {
        if (cacheLines[i][0].valid && cacheLines[i][0].tag == address.tag) {
            return HIT;
        }
    }

    // Search for a free line
    for (int i = 0; i < cfg.numSets; i++) {
        if (!cacheLines[i][0].valid) {
            cacheLines[i][0].tag = address.tag;
            cacheLines[i][0].valid = true;
            return MISS;
        }
    }

    // No free line: use random replacement
    int randomIndex = rand() % cfg.numSets;
    cacheLines[randomIndex][0].tag = address.tag;
    cacheLines[randomIndex][0].valid = true;

    return MISS;
}

cacheResType cache::cacheSimNway(addr address, const cacheConfig &cfg)
{
    int setIndex = address.index;

    // Search for HIT in the set
    for (int way = 0; way < cfg.numWays; way++) {
        if (cacheLines[setIndex][way].valid &&
            cacheLines[setIndex][way].tag == address.tag) {
            return HIT;
            }
    }

    // MISS: Try to find an empty slot
    for (int way = 0; way < cfg.numWays; ++way) {
        if (!cacheLines[setIndex][way].valid) {
            cacheLines[setIndex][way].tag = address.tag;
            cacheLines[setIndex][way].valid = true;
            return MISS;
        }
    }

    // If all are full: apply random replacement
    int randomWay = rand() % cfg.numWays;
    cacheLines[setIndex][randomWay].tag = address.tag;
    cacheLines[setIndex][randomWay].valid = true;
    return MISS;
}


