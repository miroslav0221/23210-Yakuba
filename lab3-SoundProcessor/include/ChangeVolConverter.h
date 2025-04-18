#ifndef UPVOLCONVERTER_H
#define UPVOLCONVERTER_H
#include "IConverter.h"
#include <iostream>


//vol sec_start sec_end coefficient
namespace Converter {
    class ChangeVolConverter : public IConverter {
    private:
        double coef_ = 1;
    public:
        void convert(std::vector<short int> & input) override;
        void init_coef(const double coef);
    };
}

#endif
