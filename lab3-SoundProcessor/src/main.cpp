#include <ChangeVolConverter.h>
#include <iostream>
#include <DataSource.h>
#include <Factory.h>
#include <IConverter.h>
#include <MuteConverter.h>
#include <Processor.h>
#include "MixConverter.h"

Factory::Factory<Converter::IConverter> create_factory()
{
    static Factory::Factory<Converter::IConverter> factory;
    factory.register_creator(
        "mix",
        Factory::Creator<Converter::IConverter>(
            []() -> Converter::IConverterPtr
            { return std::make_shared<Converter::MixConverter>(); }
        ));
    factory.register_creator(
        "mute",
        Factory::Creator<Converter::IConverter>(
            []() -> Converter::IConverterPtr
            { return std::make_shared<Converter::MuteConverter>(); }
        ));
    factory.register_creator(
        "vol",
        Factory::Creator<Converter::IConverter>(
            []() -> Converter::IConverterPtr
            { return std::make_shared<Converter::ChangeVolConverter>(); }
        ));

    return factory;
}

int main(int argc, char * argv[])
{
    Factory::Factory<Converter::IConverter> factory = create_factory();

    DataSource data_source;
    DataWriter data_writer;
    data_source.process_run(argc, argv);
    Processor processor(data_source, factory, data_writer);
    processor.processing_file();


    return 0;
}
