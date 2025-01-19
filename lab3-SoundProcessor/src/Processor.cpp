#include <iostream>
#include "Processor.h"
#include <ChangeVolConverter.h>
#include <sstream>
#include "IConverter.h"
#include "fstream"
#include "MuteConverter.h"
#include "MixConverter.h"

Processor::Processor(DataSource &data_source_,
    Factory::Factory<Converter::IConverter> & factory_, DataWriter & data_writer
    ) : data_source(data_source_),factory(factory_), data_writer_(data_writer) {
    converter_type =  {"mix", "mute", "vol"};
}

void Processor::processing_file() {
    WavHeader header = data_source.get_header();
    data_writer_.init_stream(data_source.get_nameout());
    data_writer_.write_header(header);
    while (data_source.get_processed_sec(0) < data_source.get_size_audio(0)) {
        data_source.reading_samples(0);
        processing_config();
        std::cout << data_source.get_processed_sec(0) << std::endl;
        data_writer_.write_sample(data_source.get_samples_sec(), data_source.get_count_samples());
    }
    std::cout<<"Обработка закончена" << std::endl;
}


void Processor::processing_config() {
    std::string config_name = data_source.get_config();
    std::ifstream file(config_name);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть конфиг файл");
    }
    std::string str;
    int current_sec = data_source.get_processed_sec(0) - 1;
    while(std::getline(file, str)) {
        if (str[0] == '#') {
            continue;
        }
        std::vector<std::string> words;
        std::istringstream stream(str);
        std::string word;
        while(stream >> word) {
            words.push_back(word);
        }
        auto it = std::find(converter_type.begin(), converter_type.end(), words[0]);
        if (it == converter_type.end()) {
            std::cout<<"Невозможное преобразование в конфиг файле"<<std::endl;
            continue;
        }
        auto converter = factory.create(words[0]);
        if (words[0] == "mute") {
            int start = std::stoi(words[1]);
            int end = std::stoi(words[2]);
            if (current_sec >= start and current_sec <= end) {
                std::shared_ptr<Converter::MuteConverter> mute_converter =
                    std::dynamic_pointer_cast<Converter::MuteConverter>(converter);
                mute_converter->convert(data_source.get_samples_sec());
                }
        }
        if (words[0] == "mix") {
            int index = std::stoi(words[1]);
            int start_mix = 0;
            if (words.size() == 3) {
                start_mix = std::stoi(words[2]);
            }

            if (current_sec >= start_mix and current_sec < data_source.get_size_audio(index)) {
                std::shared_ptr<Converter::MixConverter> mix_converter =
                    std::dynamic_pointer_cast<Converter::MixConverter>(converter);
                auto samples = data_source.reading_samples(index);
                mix_converter->init_sample(samples);
                mix_converter->convert(data_source.get_samples_sec());
                }
        }
        if (words[0] == "vol") {
            int start = std::stoi(words[1]);
            int end = std::stoi(words[2]);
            double koef = std::stoi(words[3]);
            if (current_sec >= start and current_sec <= end) {
                std::shared_ptr<Converter::ChangeVolConverter> vol_converter =
                    std::dynamic_pointer_cast<Converter::ChangeVolConverter>(converter);
                vol_converter->init_coef(koef);
                vol_converter->convert(data_source.get_samples_sec());
            }
        }

    }
}

