#ifndef MIXCONVERTER_H
#define MIXCONVERTER_H
#include "IConverter.h"
#include <iostream>

namespace Converter {

      class MixConverter : public IConverter {
      private:
          std::vector<short int> samples_for_mix;
      public:
          void convert(std::vector<short int> & input) override;
          void init_sample(const std::vector<short int>& samples_for_m);

};


}


#endif
