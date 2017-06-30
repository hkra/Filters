#pragma once

#include <bitset>
#include <vector>
#include <string>
#include <boost/dynamic_bitset.hpp>

typedef uint64 (*HashFn)(const char *s, size_t len, uint64 seed);

struct HashPair {
    HashFn fn;
    uint64 seed;
};

class BloomFilter 
{
public:

    explicit BloomFilter(size_t size, const std::vector<HashPair> & hashSet) :
        hashSet(hashSet), data(size) {
    }

    void insert(const std::string & item) {
        for (auto it = hashSet.begin(); it != hashSet.end(); ++it) {
            auto index = (*it).fn(item.c_str(), item.size(), (*it).seed) % data.size();
            data.set(index);
        }
    }

    bool exists(const std::string & item) const {
        for (auto it = hashSet.begin(); it != hashSet.end(); ++it) {
            auto index = (*it).fn(item.c_str(), item.size(), (*it).seed) % data.size();
            if (!data[index])
                return false;
        }
        return true;
    }

private:

    boost::dynamic_bitset<> data;
    const std::vector<HashPair> & hashSet;
};