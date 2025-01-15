#include "MuteConverter.h"


void Converter::MuteConverter::convert(std::vector<short int> &input) {
    input.insert(input.begin(), input.end() - input.begin(), 0);
}

