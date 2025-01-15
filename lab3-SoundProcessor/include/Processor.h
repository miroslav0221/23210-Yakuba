#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "DataSource.h"
#include "Factory.h"
#include "DataWriter.h"
class Processor {
private:
    DataSource & data_source;
    Factory::Factory<Converter::IConverter> & factory;
    DataWriter & data_writer_;
    std::vector<std::string> converter_type;
public:
    Processor(DataSource & data_source_,
        Factory::Factory<Converter::IConverter> & factory_,
        DataWriter & data_writer);

    void processing_file();

    void processing_config();

};

#endif
