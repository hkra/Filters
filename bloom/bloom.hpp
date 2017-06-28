#pragma once

#include <bitset>
#include <vector>
#include <city.h>

typedef uint64 (*HashFn)(const char *s, size_t len, uint64 seed);

struct HashPair {
    HashFn fn;
    uint64 seed;
};

template<typename T>
class BloomFilter 
{
public:

    explicit BloomFilter(const std::vector<HashPair> & hashSet) :
        hashSet(hashSet) {
    }

private:

    std::bitset<512> data;
    const std::vector<HashPair> & hashSet;
};