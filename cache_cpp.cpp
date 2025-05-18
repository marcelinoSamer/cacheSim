#include <iostream>
#include <iomanip>
#include "cache_h.h"

using namespace std;


cache::cache(cacheConfig cfg) {
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
cacheResType cache::cacheSimDM(addr addr, const cacheConfig &cfg)
{
    // This function accepts the memory address for the memory transaction and
    // returns whether it caused a cache miss or a cache hit
    // The current implementation assumes there is no cache; so, every transaction is a miss 
    
    if (cacheLines[addr.index][addr.offset].tag == tag)
        return HIT;

    cacheLines[index][offset].tag = tag;
    return MISS;
}
// Fully Associative Cache Simulator
cacheResType cache::cacheSimFA(unsigned int addr)
{
    // This function accepts the memory address for the read and
    // returns whether it caused a cache miss or a cache hit
    // The current implementation assumes there is no cache; so, every transaction is a miss 
    return MISS;
}
