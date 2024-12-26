#include "csvparser.h"
#include <iostream>

int main(int argc, char** argv){
    auto in = std::string(argv[1]);
    std::ifstream fin(in);
    CSVParser<int, std::string, int, int> parser(fin, 0);
    for(auto& it : parser) {
        std::cout << it << std::endl;
    }

    return 0;
}

