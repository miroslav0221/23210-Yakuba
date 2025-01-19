#include "ChangeVolConverter.h"
#include <iostream>
#define SIZE_SHORT_ 32767

void Converter::ChangeVolConverter::convert(std::vector<short int> &input) {
    for (auto& element : input) {
        double element_ = element * coef_;
        if (element_ > SIZE_SHORT_) {
            element_ = SIZE_SHORT_;
        }
        if (element_ < (-1)*SIZE_SHORT_ - 1) {
            element_ = SIZE_SHORT_*(-1) - 1;
        }
        element = static_cast<short int>(element_);
    }
}

void Converter::ChangeVolConverter::init_coef(const double coef) {
    coef_ = coef;
}
