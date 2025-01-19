#include "MixConverter.h"
#include <iostream>

void Converter::MixConverter::convert(std::vector<short int> &input) {
    for (int i = 0; i < input.size(); i++) {
        input[i] = static_cast<short int>((input[i] + samples_for_mix[i]) / 2);
    }
}

void Converter::MixConverter::init_sample(const std::vector<short int>& samples_for_m) {
    samples_for_mix = samples_for_m;
}


