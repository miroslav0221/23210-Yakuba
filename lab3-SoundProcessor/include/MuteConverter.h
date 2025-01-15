#ifndef MUTECONVERTER_H
#define MUTECONVERTER_H
#include "IConverter.h"
#include <iostream>

namespace Converter {
    class MuteConverter : public IConverter {
    public:

        void convert(std::vector<short int> & input) override;

    };


}


#endif