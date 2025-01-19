#ifndef ICONVERTER_H
#define ICONVERTER_H
#include <iostream>

namespace Converter {

    class IConverter {
    public:
          virtual ~IConverter() = default;
          virtual void convert(std::vector<short int> & input) {};


    };

    using IConverterPtr = std::shared_ptr<IConverter>;
}



#endif