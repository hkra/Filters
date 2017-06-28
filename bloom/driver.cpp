#include <vector>
#include <string>
#include "bloom.hpp"

int main(int argc, char * argv[])
{
    using namespace std;

    const vector<HashPair> defaultHashSet {
        { CityHash64WithSeed, 0xDEADBEEFCAFEBABE },
        { CityHash64WithSeed, 0xCAFEBABEDEADBEEF },
        { CityHash64WithSeed, 0xDFDBEEEAFCAEBABE }
    };

    BloomFilter<string> filter(defaultHashSet);

    return 0;
}