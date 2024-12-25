#ifndef READER_H
#define READER_H
#include <iostream>
#include "Model.h"

class Handler_file {

      Model & model;

public:

      explicit Handler_file(Model & model);
      void read_file(const std::string & filename) const;
      void write_file(const std::string & filename) const;
};

#endif
