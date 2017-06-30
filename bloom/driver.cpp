#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include <city.h>

#include "bloom.hpp"

using namespace std;
namespace po = boost::program_options;

const size_t DEFAULT_FILTER_SIZE = 1 << 16;

const vector<HashPair> DEFAULT_HASH_SET {
    { CityHash64WithSeed, 0xDEADBEEFCAFEBABE },
    { CityHash64WithSeed, 0xFEED0DEEDCE11BAD },
    { CityHash64WithSeed, 0xDECAF00000DECADE },
    { CityHash64WithSeed, 0xC0FFEEBEDBEADFAD }
};

namespace {
    po::variables_map* ParseProgramArgs(int argc, char* argv[], po::options_description& desc)
    {
        auto vm = new po::variables_map;
        po::positional_options_description p;
        p.add("input-file", -1);

        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), *vm);
        po::notify(*vm);
        return vm;
    }
}

void populate_filter(istream & in, BloomFilter & filter) {
    string url;
    while (in >> url) {
        filter.insert(url);
    }
}

int main(int argc, char * argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("input-file", po::value<string>(), "input file")
        ("size,s",   po::value<size_t>()->default_value(DEFAULT_FILTER_SIZE), "Set filter size (in bits)")
        ("help",      "Print help message");

    auto argVars = std::unique_ptr<po::variables_map>(ParseProgramArgs(argc, argv, desc));

    if (argVars->count("help")) {
        cout << desc << endl;
        return 0;
    }

    if (argVars->count("input-file") != 1) {
        cerr << "exactly one input file is required" << endl;
        return 1;
    }

    fstream fs;
    fs.open((*argVars)["input-file"].as<string>(), fstream::in);

    if (!fs.is_open()) {
        cerr << "unable to open file: " << argv[1] << "\n";
    }

    size_t filterSize = (*argVars)["size"].as<size_t>();
    BloomFilter filter(filterSize, DEFAULT_HASH_SET);
    populate_filter(fs, filter);
    return 0;
}